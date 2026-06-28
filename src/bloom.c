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

unsigned int gerarHash(char *nome, int numeroHash)
{
    return (hash1(nome) + numeroHash * hash2(nome)) % M;
}

BloomFilter *criarBloom(void)
{
    BloomFilter *novo = malloc(sizeof(BloomFilter));

    if (novo == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < (M + 7) / 8; i++)
    {
        novo->bits[i] = 0;
    }

    novo->totalConsultas = 0;
    novo->consultasIgnoradas = 0;
    novo->falsosPositivos = 0;

    return novo;
}

void inserirBloom(BloomFilter *bloom, char *nome)
{
    for (int i = 0; i < K; i++)
    {
        unsigned int posicao = gerarHash(nome, i);

        unsigned int byte = posicao / 8;
        unsigned int bit = posicao % 8;

        bloom->bits[byte] |= (1u << bit);
    }
}

bool consultarBloom(BloomFilter *bloom, char *nome)
{
    bloom->totalConsultas++;

    for (int i = 0; i < K; i++)
    {
        unsigned int posicao = gerarHash(nome, i);

        unsigned int byte = posicao / 8;
        unsigned int bit = posicao % 8;

        if ((bloom->bits[byte] & (1u << bit)) == 0)
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
    free(bloom);
}