#include "../includes/bloom.h"

unsigned int hash1(char *nome)
{
    unsigned int hash = 5381;

    while (*nome)
    {
        hash = ((hash << 5) + hash) + (unsigned char)*nome++;
    }

    return hash;
}

unsigned int hash2(char *nome)
{
    unsigned int hash = 0;

    while (*nome)
    {
        hash = hash * 131 + (unsigned char)*nome++;
    }

    return hash;
}

unsigned int gerarHash(char *nome, int numeroHash, int tamanho)
{
    return (hash1(nome) + numeroHash * hash2(nome)) % tamanho;
}

BloomFilter *criarBloom(int tamanho, int quantidadeHashes)
{
    BloomFilter *novo = (BloomFilter *) malloc(sizeof(BloomFilter));

    if (novo == NULL)
    {
        return NULL;
    }

    novo->bits = (unsigned char *) calloc((tamanho + 7) / 8, sizeof(unsigned char));

    if (novo->bits == NULL)
    {
        free(novo);
        return NULL;
    }

    novo->tamanho = tamanho;
    novo->quantidadeHashes = quantidadeHashes;

    novo->totalConsultas = 0;
    novo->consultasIgnoradas = 0;
    novo->falsosPositivos = 0;

    return novo;
}

void inserirBloom(BloomFilter *bloom, char *nome)
{
    for (int i = 0; i < bloom->quantidadeHashes; i++)
    {
        int posicao = gerarHash(nome, i, bloom->tamanho);

        int byte = posicao / 8;
        int bit = posicao % 8;

        bloom->bits[byte] |= (1 << bit);
    }
}

bool consultarBloom(BloomFilter *bloom, char *nome)
{
    bloom->totalConsultas++;

    for (int i = 0; i < bloom->quantidadeHashes; i++)
    {
        int posicao = gerarHash(nome, i, bloom->tamanho);

        int byte = posicao / 8;
        int bit = posicao % 8;

        if (!(bloom->bits[byte] & (1 << bit)))
        {
            bloom->consultasIgnoradas++;
            return false;
        }
    }

    return true;
}

void registrarFalsoPositivo(BloomFilter *bloom)
{
    bloom->falsosPositivos++;
}

double taxaFalsoPositivo(BloomFilter *bloom)
{
    if (bloom->totalConsultas == 0)
    {
        return 0.0;
    }

    return (100.0 * bloom->falsosPositivos) / bloom->totalConsultas;
}

void liberarBloom(BloomFilter *bloom)
{
    free(bloom->bits);
    free(bloom);
}