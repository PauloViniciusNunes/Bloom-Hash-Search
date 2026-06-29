#ifndef USUARIO_H
#define USUARIO_H

#include "hash.h"
#include "bloom.h"


void menu();
void inserirUsuario(FILE *file, BloomFilter *filtro, hashTable *tabela, const char* usuario);
void buscarUsuario(BloomFilter *filtro, hashTable *tabela, const char* usuario);
double tempomedio_busca(FILE *file, hashTable *tabela)

#endif