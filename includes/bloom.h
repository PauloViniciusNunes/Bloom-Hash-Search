#ifndef BLOOM_H
#define BLOOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define M 959000                  // Número de bits do Bloom Filter
#define K 2                       // Número de funções hash

typedef unsigned char bloomfilter[(M + 7) / 8];

typedef struct BloomFilter
{
    bloomfilter bits;

    long totalConsultas;
    long consultasIgnoradas;
    long falsosPositivos;

} BloomFilter;


/* Funções Hash */
unsigned int hash1(char *nome);

unsigned int hash2(char *nome);

unsigned int gerarHash(char *nome, int numeroHash);


/* Bloom Filter */
BloomFilter *criarBloom(void);

void inserirBloom(BloomFilter *bloom, char *nome);

bool consultarBloom(BloomFilter *bloom, char *nome);

void registrarFalsoPositivo(BloomFilter *bloom);

double taxaFalsoPositivo(BloomFilter *bloom);

void liberarBloom(BloomFilter *bloom);

#endif