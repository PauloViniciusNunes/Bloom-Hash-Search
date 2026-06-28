#include "benchmark.h"
#include "hash.h"
#include "bloom.h"



void gerarArquivo(const char *arq, int num_reg, hashTable *tabela, bloomfilter *filtro) {
    FILE *file = fopen(arq, "w");
    if(!file) {
        printf("Nao foi possivel gerar o arquivo!\n");
        return;
    }

    char usuario[12] = '\0';
    int i, j;
    for(i = 0; i < num_reg; i++) {
        for(j = 0; j < 8; j++) {
        usuario[j] = 'a' + rand()%26;
        }
        for(j = 8; j < 11; j++) {
            usuario[j] = '0' + rand()%10;
        }
        if(!consultarBloom(filtro, usuario)) {
            inserirHash(tabela, usuario);
            inserirBloom(filtro, usuario);
            fprintf(file, "%s\n", usuario);
        } else if(!buscarHash(tabela, usuario)) {
            inserirHash(tabela, usuario);
            inserirBloom(filtro, usuario);
            fprintf(file, "%s\n", usuario);
        } else {
            i--;
            continue;
        }
    }
    fclose(file);
}

void processarArquivo(const char *arq, int num_reg, hashTable *tabela, bloomfilter *filtro) {
    FILE *file = fopen(arq, "r");
    FILE *result = fopen("./resultados/resultados.csv", "a");
    if(!file || !result) {
        printf("Nao foi possivel processar o arquivo!\n");
        return -1;
    }

    clock_t t;
    char usuario[12], str[30];
    double cpu_time_used, fp;
    sprintf(str, "%d", num_reg);
    fprintf(result, "%s;", str);

    t = clock();
    while(fscanf(file, "%s", usuario)) {
        buscarHash(tabela, usuario);
    }
    t = clock() - t;
    cpu_time_used = ((double) t)/CLOCKS_PER_SEC;
    sprintf(str, "%f", cpu_time_used);
    fprintf(result, "%s;", str);

    fseek(file, 0, SEEK_SET);
    t = clock();
    while(fscanf(file, "%s", usuario)) {
        if(!consultarBloom(filtro, usuario)) {
            buscarHash(tabela, usuario);
        }
    }
    t = clock() - t;
    cpu_time_used = ((double) t)/CLOCKS_PER_SEC;
    sprintf(str, "%f", cpu_time_used);
    fprintf(result, "%s;", str);

    fclose(file);

    fp = taxaFalsoPositivo(filtro);
    sprintf(str, "%f", cpu_time_used);
    fprintf(result, "%s\n", str);

    fclose(result);

    destruirTabela(tabela);
    liberarBloom(filtro);
}