#include <stdio.h>
#include "../includes/bloom.h"
#include "../includes/hash.h"

void menu() {
    printf("=================================================\n");
    printf("Sistema de Verificação de Cadastro de Usuários\n");
    printf("=================================================\n");
    printf("[ 1 ] - INSERIR\n");
    printf("[ 2 ] - CONSULTAR\n");
    printf("[ 3 ] - EXIBIR ESTATISTICAS\n");
    printf("[ 4 ] - INSERIR EM LOTE\n");
    printf("[ 5 ] - SAIR\n");
}

int main() {
    FILE *file_aux;
    char arq[20];
    char aux[40] = "./data/";

    FILE *file = fopen("./data/usuarios.txt", "a+");
    if(!file) {
        printf("nao foi possivel abrir o arquivo base de usuarios\n");
        return -1;
    }
    fseek(file, 0, SEEK_SET);

    BloomFilter *filtro = criarBloom();
    hashTable *tabela = criarHash();
    char usuario[20];

    // Carrega os dados existentes salvos no arquivo base
    while(fscanf(file, "%s", usuario) != EOF) { // CORREÇÃO: Evita travamento no boot
        inserirHash(tabela, usuario);
        inserirBloom(filtro, usuario);
    }

    int op;
    do {
        menu();
        if (scanf("%d", &op) != 1) break;
        
        switch(op) {
            case 1:
                printf("Digite o usuario inserido: ");
                scanf("%s", usuario);
                if(!consultarBloom(filtro, usuario) || !buscarHash(tabela, usuario)) {
                    inserirHash(tabela, usuario);
                    inserirBloom(filtro, usuario);
                    fprintf(file, "%s\n", usuario);
                    printf("Usuario cadastrado com sucesso!\n");
                } else {
                    printf("Usuario ja cadastrado!\n");
                }
                break;
            case 2:
                printf("Digite o usuario pesquisado: ");
                scanf("%s", usuario);
                // Lógica de proteção do Bloom Filter agindo antes da Hash
                if(!consultarBloom(filtro, usuario)) {
                    printf("Usuario inexistente (Negado pelo Bloom Filter)\n");
                } else if(!buscarHash(tabela, usuario)) {
                    registrarFalsoPositivo(filtro); // Registra que o bloom errou
                    printf("Usuario inexistente (Falso Positivo detectado na Hash)\n");
                } else {
                    printf("Usuario encontrado com sucesso!\n");
                }
                break;
            case 3:
                printf("\n--- ESTATÍSTICAS DO FILTRO DE BLOOM ---\n");
                printf("Total de consultas realizadas: %ld\n", filtro->totalConsultas);
                printf("Consultas barradas direto no Bloom: %ld\n", filtro->consultasIgnoradas);
                printf("Falsos positivos encontrados: %ld\n", filtro->falsosPositivos);
                printf("Taxa de Falsos Positivos: %.2f%%\n\n", taxaFalsoPositivo(filtro));
                break;
            case 4:
                printf("Digite o nome do arquivo (ex: novos.txt): ");
                scanf("%s", arq);
                strcat(aux, arq);
                file_aux = fopen(aux, "r");
                if(!file_aux) {
                    printf("Erro ao abrir arquivo em lote.\n");
                    strcpy(aux, "./data/");
                    break;
                }
                while(fscanf(file_aux, "%s", usuario) != EOF) { // CORREÇÃO: loop corrigido
                    if(!consultarBloom(filtro, usuario) || !buscarHash(tabela, usuario)) {
                        inserirHash(tabela, usuario);
                        inserirBloom(filtro, usuario);
                        fprintf(file, "%s\n", usuario);
                    }
                }
                fclose(file_aux);
                strcpy(aux, "./data/");
                printf("Lote processado com sucesso.\n");
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