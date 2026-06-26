#ifndef BLOOM_H
#define BLOOM_H

#include "hash.h"

typedef struct {
    unsigned char *bits;
    int m;
    int k;
    long consultas;
    long consultasEvitadas;
    long falsosPositivos;
} BloomFilter;

BloomFilter* criarBloom(int m, int k);

void inserirBloom(BloomFilter *bf, char *str);

int consultarBloom(BloomFilter *bf, char *str);

void liberarBloom(BloomFilter *bf);

int consultarSistema(BloomFilter *bf, Hash *hash, char *usuario);

double taxaFalsoPositivo(BloomFilter *bf);

#endif
