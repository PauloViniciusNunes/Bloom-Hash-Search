#include "../includes/bloom.h"


/* ---------------- HASHES ---------------- */

unsigned int hash1(char *nome)
{
    unsigned int hash = 5381;

    while(*nome)
    {
        hash = ((hash << 5) + hash) + (unsigned char)*nome;
        nome++;
    }

    return hash;
}


unsigned int hash2(char *nome)
{
    unsigned int hash = 0;

    while(*nome)
    {
        hash = hash * 131 + (unsigned char)*nome;
        nome++;
    }

    return hash;
}


/* Calcula uma posição do vetor usando Double Hashing */

unsigned int calcularPosicao(char *nome, int numeroHash, int tamanho)
{
    unsigned int h1 = hash1(nome);
    unsigned int h2 = hash2(nome);

    return (h1 + numeroHash * h2) % tamanho;
}


/* ---------------- BITS ---------------- */


/* Liga um bit */

void ligarBit(BloomFilter *bloom, int posicao)
{
    int byte = posicao / 8;

    int bit = posicao % 8;

    bloom->bits[byte] |= (1 << bit);
}


/* Verifica se um bit está ligado */

bool bitLigado(BloomFilter *bloom, int posicao)
{
    int byte = posicao / 8;

    int bit = posicao % 8;

    return (bloom->bits[byte] & (1 << bit));
}


/* ---------------- BLOOM ---------------- */


BloomFilter* criarBloom(int tamanho, int numHashes)
{
    BloomFilter *bloom =
        malloc(sizeof(BloomFilter));

    if(bloom == NULL)
        return NULL;

    bloom->tamanho = tamanho;
    bloom->numHashes = numHashes;

    bloom->bits =
        calloc((tamanho + 7) / 8, sizeof(unsigned char));

    if(bloom->bits == NULL)
    {
        free(bloom);
        return NULL;
    }

    bloom->totalConsultas = 0;
    bloom->consultasIgnoradas = 0;
    bloom->falsosPositivos = 0;

    return bloom;
}


/* Insere um nome */

void inserirBloom(char *nome, BloomFilter *bloom)
{
    for(int i=0; i<bloom->numHashes; i++)
    {
        int posicao;

        posicao =
            calcularPosicao(nome, i, bloom->tamanho);

        ligarBit(bloom, posicao);
    }
}


/* Consulta */

bool buscarBloom(char *nome, BloomFilter *bloom)
{
    bloom->totalConsultas++;

    for(int i=0; i<bloom->numHashes; i++)
    {
        int posicao;

        posicao =
            calcularPosicao(nome, i, bloom->tamanho);

        if(!bitLigado(bloom, posicao))
        {
            bloom->consultasIgnoradas++;

            return false;
        }
    }

    return true;
}


/* Utilizada quando o Hash disser que o elemento não existe */

void registrarFalsoPositivo(BloomFilter *bloom)
{
    bloom->falsosPositivos++;
}


/* Calcula a taxa de falsos positivos */

double taxaFalsoPositivo(BloomFilter *bloom)
{
    if(bloom->totalConsultas == 0)
        return 0;

    return (100.0 * bloom->falsosPositivos)/ bloom->totalConsultas;
}


/* Liberação de memória */

void destruirBloom(BloomFilter *bloom)
{
    free(bloom->bits);

    free(bloom);
}