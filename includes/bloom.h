#ifndef BLOOM_H
#define BLOOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BloomFilter
{
    unsigned char *bits;

    int tamanho;
    int quantidadeHashes;

    long totalConsultas;
    long consultasIgnoradas;
    long falsosPositivos;

} BloomFilter;


/* Funções Hash */
unsigned int hash1(char *nome);
unsigned int hash2(char *nome);
unsigned int gerarHash(char *nome, int numeroHash, int tamanho);


/* Bloom Filter */
BloomFilter *criarBloom(int tamanho, int quantidadeHashes);

void inserirBloom(BloomFilter *bloom, char *nome);

bool consultarBloom(BloomFilter *bloom, char *nome);

void registrarFalsoPositivo(BloomFilter *bloom);

double taxaFalsoPositivo(BloomFilter *bloom);

void liberarBloom(BloomFilter *bloom);

#endif