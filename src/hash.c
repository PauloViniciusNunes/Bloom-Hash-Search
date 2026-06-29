#include "hash.h"

unsigned int Hash(const char *nome)
{
    unsigned int hash = 5381;
    while (*nome)
        hash = ((hash << 5) + hash) + (unsigned char)*nome++;
    return hash % N;
}

hashTable *criarHash(void) {
    hashTable *novo = malloc(sizeof(hashTable));
    if(novo == NULL) {
        return NULL;
    }
    for(int i = 0; i < N; i++) {
        novo->hash[i] = NULL;
    }
    novo->qtd = 0;
    return novo; // CORREÇÃO: Adicionado retorno da tabela
}

char *removerPrefixo(char *str, const char *prefixo)
{
    size_t tam = strlen(prefixo);
    if (strncmp(str, prefixo, tam) == 0)
        return str + tam;
    return str;
}

User* criarUsuario(const char* nome)
{
    User* novo = (User*)malloc(sizeof(User));
    if(!novo) return NULL;

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->nextUser = NULL;
    return novo;
}

void inserirHash(hashTable *tabela, const char *nome)
{
    unsigned int idx = Hash(nome);
    User *novo = criarUsuario(nome);

    if (novo == NULL) {
        printf("\n[ERRO] Falha na alocação.\n\n");
        return;
    }

    novo->nextUser = tabela->hash[idx];
    tabela->hash[idx] = novo;
    tabela->qtd++;
}

User *buscarHash(hashTable *tabela, const char *nome)
{
    unsigned int idx = Hash(nome);
    User *consultado = tabela->hash[idx];

    while (consultado != NULL) {
        if (strcmp(consultado->nome, nome) == 0) {   
            return consultado;
        }
        consultado = consultado->nextUser;
    }
    return NULL;
}

void destruirTabela(hashTable *tabela)
{
    if (!tabela) return;
    for (int i = 0; i < N; i++) {
        User *p = tabela->hash[i];
        while (p) {
            User *aux = p;
            p = p->nextUser;
            free(aux);
        }
    }
    free(tabela);
}

void interpretarComando(char* comando, hashTable *tabela)
{
    // CORREÇÃO: Nomes das funções sincronizados com hash.h
    if(strstr(comando, "INSERIR") != NULL) {
        char *nome = removerPrefixo(comando, "INSERIR ");
        inserirHash(tabela, nome);
    }
    else if(strstr(comando, "CONSULTAR") != NULL) {
        char *nome = removerPrefixo(comando, "CONSULTAR ");
        buscarHash(tabela, nome);
    }
    else if(strstr(comando, "SAIR") != NULL) {
        destruirTabela(tabela);
        exit(EXIT_SUCCESS);
    }
    else {
        printf("\n[ERROR] COMANDO DESCONHECIDO.\n\n");
    }
}