#include "bloom.h"
#include "hash.h"
#include "usuario.h"

int main() {
    FILE *file2;
    char arq[20];
    char path[50] = "./data/";

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
        scanf("%d", &op);
        
        switch(op) {
            case 1:
                printf("Digite o usuario inserido: ");
                scanf("%s", usuario);
                inserirUsuario(file, filtro, tabela, usuario);
                break;
            case 2:
                printf("Digite o usuario pesquisado: ");
                scanf("%s", usuario);
                buscarUsuario(filtro, tabela, usuario);
                break;
            case 3:
                printf("\n--- ESTATÍSTICAS ---\n");
                printf("Total de elementos armazenados na tabela Hash: %ld\n", tabela->qtd);
                printf("Total de consultas realizadas: %ld\n", filtro->totalConsultas);
                printf("Consultas barradas direto no Bloom: %ld\n", filtro->consultasIgnoradas);
                printf("Falsos positivos encontrados: %ld\n", filtro->falsosPositivos);
                printf("Taxa de Falsos Positivos: %.2f%%\n", taxaFalsoPositivo(filtro));
                printf("Tempo medio consulta: %lf\n\n", tempomedio_busca(file, tabela));
                break;
            case 4:
                printf("Digite o nome do arquivo (ex: novos.txt): ");
                scanf("%s", arq);
                strcat(path, arq);
                file2 = fopen(path, "r");
                if(!file2) {
                    printf("Erro ao abrir arquivo em lote.\n");
                    strcpy(path, "./data/");
                    break;
                }
                while(fscanf(file2, "%s", usuario) != EOF) { // CORREÇÃO: loop corrigido
                    inserirUsuario(file, filtro, tabela, usuario);
                }
                fclose(file2);
                strcpy(path, "./data/");
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