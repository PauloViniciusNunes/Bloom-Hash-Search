#ifndef BLOOM_H
#define BLOOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BloomFilter
{
    unsigned char *bits;

    int tamanho;
    int numHashes;

    long totalConsultas;
    long consultasIgnoradas;
    long falsosPositivos;

} BloomFilter;


/* Criação e destruição */
BloomFilter* criarBloom(int tamanho, int numHashes);
void destruirBloom(BloomFilter *bloom);


/* Inserção e consulta */
void inserirBloom(char *nome, BloomFilter *bloom);
bool buscarBloom(char *nome, BloomFilter *bloom);


/* Estatísticas */
void registrarFalsoPositivo(BloomFilter *bloom);
double taxaFalsoPositivo(BloomFilter *bloom);

#endif