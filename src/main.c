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
    FILE *file = fopen("../data/usuarios.txt", "a+");
    if(!file) {
        printf("nao foi possivel abrir o arquivo\n");
        return -1;
    }
    fseek(file, 0, SEEK_SET);

    BloomFilter *filtro = criarBloom(244, 2);
    Hash tabela;
    char usuario[20];
    while(fscanf(file, "%s", usuario)) {
        inserirUsuario(usuario, tabela);
        inserirBloom(filtro, usuario);
    }

    int op;
    do {
        menu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Digite o nome de usuario: ");
                scanf("%s", usuario);
                if(!consultarBloom(filtro, usuario)) {
                    inserirUsuario(usuario, tabela);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                } else {
                    printf("Usuario ja cadastrado!\n");
                }
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            default: printf("Digite uma opcao valida\n");
        }
    } while(op != 5);

    fclose(file);
    liberarBloom(filtro);
    
    return 0;
}