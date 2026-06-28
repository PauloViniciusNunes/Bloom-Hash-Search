#include <stdio.h>
#include "bloom.h"
#include "hash.h"

void menu() {
    printf("=================================================\n");
    printf("Sistema de Verificação de Cadastro de Usuários\n");
    printf("=================================================\n");
    printf("[ 1 ] - INSERIR\n");
    printf("[ 2 ] - CONSULTAR\n");
    printf("[ 3 ] - EXIBIR ESTATISTICAS\n");
    printf("[ 4 ] - INSERRIR EM LOTE\n");
    printf("[ 5 ] - SAIR\n");
}

int main() {
    FILE *file_aux;
    char arq[20];
    char aux[20] = "../data/";

    FILE *file = fopen("../data/usuarios.txt", "a+");
    if(!file) {
        printf("nao foi possivel abrir o arquivo\n");
        return -1;
    }
    fseek(file, 0, SEEK_SET);

    BloomFilter *filtro = criarBloom();
    hashTable *tabela = criarHash();
    char usuario[20];
    while(fscanf(file, "%s", usuario)) {
        inserirUsuario(tabela, usuario);
        inserirBloom(filtro, usuario);
    }

    int op;
    do {
        menu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Digite o usuario inserido: ");
                scanf("%s", usuario);
                if(!consultarBloom(filtro, usuario)) {
                    inserirUsuario(tabela, usuario);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                } else if(!buscarUsuario(tabela, usuario)) {
                    inserirUsuario(tabela, usuario);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                } else {
                    printf("Usuario ja cadastrado!\n");
                }
                break;
            case 2:
                printf("Digite o usuario pesquisado: ");
                scanf("%s", usuario);
                if(!consultarBloom(filtro, usuario)) {
                    printf("Usiario inexistente\n");
                } else if(!buscarUsuario(tabela, usuario)) {
                    printf("Usiario inexistente\n");
                } else {
                    printf("Usuario encontrado!\n");
                }
                break;
            case 3:

            case 4:
                printf("Digite o nome do arquivo: ");
                scanf("%s", arq);
                strcat(aux, arq);
                file_aux = fopen(aux, "r+");
                while(fscanf(file, "%s", usuario)) {
                    if(!consultarBloom(filtro, usuario)) {
                    inserirUsuario(tabela, usuario);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                    } else if(!buscarUsuario(tabela, usuario)) {
                    inserirUsuario(tabela, usuario);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                    } else {
                    printf("Usuario ja cadastrado!\n");
                    }
                }
                fclose(file_aux);
                strcpy(aux, "../data/");
                break;
            case 5:
                fflush(file);
                break;
            default: printf("Digite uma opcao valida\n");
        }
    } while(op != 5);

    fclose(file);
    liberarBloom(filtro);
    destruirTabela(tabela);
    
    return 0;
}