#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define N 200003

typedef struct User {
    char nome[81];
    struct User *nextUser; 
} User;

typedef struct hashTable {
    User* hash[N];
    long qtd;
    long colisoes;
    long ocupacao;
} hashTable;

hashTable* criarHash(void);
User* criarUsuario(const char* nome);
unsigned int Hash(const char* nome);
void interpretarComando(char *comando, hashTable *tabela);
void inserirHash(hashTable *tabela, const char* nome);
User* buscarHash(hashTable *tabela, const char* nome);
char *removerPrefixo(char *str, const char *prefixo);
void destruirTabela(hashTable *tabela);

#endif