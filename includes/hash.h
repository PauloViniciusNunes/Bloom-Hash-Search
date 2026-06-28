#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
# define N 200003

typedef struct User {
    char nome [81];
    struct User *nextUser; // Para encadeamento externo
} User;

typedef struct User* Hash[ N ];

typedef struct hashTable {
    Hash hash;
    int qtd;
} hashTable;

hashTable* criarHash();
User* criarUsuario(char* nome);
unsigned int gerarHash(char* nome);
void interpretarComando(char * comando, Hash tabela);
void inserirUsuario(char* nome, hashTable *tabela);
User* buscarUsuario(char* nome, hashTable *tabela);
char *removerPrefixo(char *str, const char *prefixo);
void destruirTabela(hashTable *tabela);

#endif
