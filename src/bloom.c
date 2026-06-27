#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bloom.h"


/* Função hash 1 */
unsigned int hash1(char *texto)
{
    unsigned int hash = 5381;

    while(*texto)
    {
        hash = ((hash << 5) + hash) + *texto;
        texto++;
    }

    return hash;
}


/* Função hash 2 */
unsigned int hash2(char *texto)
{
    unsigned int hash = 0;

    while(*texto)
    {
        hash = hash * 131 + *texto;
        texto++;
    }

    return hash;
}


/* Gera a posição que será utilizada no vetor */
unsigned int calcularPosicao(char *texto, int numeroHash, int tamanhoVetor)
{
    unsigned int h1 = hash1(texto);

    unsigned int h2 = hash2(texto);

    return (h1 + numeroHash * h2) % tamanhoVetor;
}


/* Liga um bit do vetor */
void ligarBit(BloomFilter *bf, int posicao)
{
    int byte = posicao / 8;

    int bit = posicao % 8;

    bf->bits[byte] |= (1 << bit);
}


/* Verifica se um bit está ligado */
int verificarBit(BloomFilter *bf, int posicao)
{
    int byte = posicao / 8;

    int bit = posicao % 8;

    return bf->bits[byte] & (1 << bit);
}


/* Inicializa todas as estatísticas */
void inicializarEstatisticas(BloomFilter *bf)
{
    bf->consultas = 0;

    bf->consultasEvitadas = 0;

    bf->falsosPositivos = 0;
}


/* Cria o Bloom */
BloomFilter* criarBloom(int tamanhoVetor, int quantidadeHashes)
{
    BloomFilter *bf;

    bf = malloc(sizeof(BloomFilter));

    bf->tamanhoVetor = tamanhoVetor;

    bf->quantidadeHashes = quantidadeHashes;

    bf->bits = calloc((tamanhoVetor + 7) / 8, sizeof(unsigned char));

    inicializarEstatisticas(bf);

    return bf;
}


/* Insere um usuário */
void inserirBloom(BloomFilter *bf, char *usuario)
{
    int i;

    for(i = 0; i < bf->quantidadeHashes; i++)
    {
        int posicao;

        posicao = calcularPosicao(usuario, i, bf->tamanhoVetor);

        ligarBit(bf, posicao);
    }
}


/* Consulta um usuário */
int consultarBloom(BloomFilter *bf, char *usuario)
{
    int i;

    bf->consultas++;

    for(i = 0; i < bf->quantidadeHashes; i++)
    {
        int posicao;

        posicao = calcularPosicao(usuario, i, bf->tamanhoVetor);

        if(!verificarBit(bf, posicao))
        {
            bf->consultasEvitadas++;

            return 0;
        }
    }

    return 1;
}


/* Calcula a taxa de falsos positivos */
double taxaFalsoPositivo(BloomFilter *bf)
{
    if(bf->consultas == 0)
        return 0;

    return (100.0 * bf->falsosPositivos) /
            bf->consultas;
}


/* Libera memória */
void liberarBloom(BloomFilter *bf)
{
    free(bf->bits);

    free(bf);
}