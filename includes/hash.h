#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 200003

typedef struct User {
    char nome[81];
    struct User *nextUser; 
} User;

typedef struct hashTable {
    User* hash[N];
    int qtd;
} hashTable;

hashTable* criarHash(void);
User* criarUsuario(char* nome);
unsigned int gerarHash(char* nome);
void interpretarComando(char *comando, hashTable *tabela);
void inserirHash(hashTable *tabela, char* nome);
User* buscarHash(hashTable *tabela, char* nome);
char *removerPrefixo(char *str, const char *prefixo);
void destruirTabela(hashTable *tabela);

#endif