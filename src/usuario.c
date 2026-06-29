#include "usuario.h"

void menu() {
    printf("=================================================\n");
    printf("Sistema de Verificacao de Cadastro de Usuarios\n");
    printf("=================================================\n");
    printf("[ 1 ] - INSERIR\n");
    printf("[ 2 ] - CONSULTAR\n");
    printf("[ 3 ] - EXIBIR ESTATISTICAS\n");
    printf("[ 4 ] - INSERIR EM LOTE\n");
    printf("[ 5 ] - SAIR\n");
}

void inserirUsuario(FILE *file, BloomFilter *filtro, hashTable *tabela, const char* usuario) {
    if(!consultarBloom(filtro, usuario) || !buscarHash(tabela, usuario)) {
        inserirHash(tabela, usuario);
        inserirBloom(filtro, usuario);
        fprintf(file, "%s\n", usuario);
        printf("Usuario cadastrado com sucesso!\n");
    } else {
        printf("Usuario ja cadastrado!\n");
    }
}

void buscarUsuario(BloomFilter *filtro, hashTable *tabela, const char* usuario) {
    // Lógica de proteção do Bloom Filter agindo antes da Hash
    if(!consultarBloom(filtro, usuario)) {
        printf("Usuario inexistente (Negado pelo Bloom Filter)\n");
    } else if(!buscarHash(tabela, usuario)) {
        registrarFalsoPositivo(filtro); // Registra que o bloom errou
        printf("Usuario inexistente (Falso Positivo detectado na Hash)\n");
    } else {
        printf("Usuario encontrado com sucesso!\n");
    }
}