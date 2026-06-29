#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"
#include "bloom.h"

// CORREÇÃO: Alterado de bloomfilter* para BloomFilter*
void gerarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro);
void processarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro);

#endif