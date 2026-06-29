#include "benchmark.h"

void gerarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro) {
    FILE *file = fopen(arq, "w");
    if(!file) {
        printf("Nao foi possivel gerar o arquivo!\n");
        return;
    }

    char usuario[12];
    int i, j;
    for(i = 0; i < num_reg; i++) {
        for(j = 0; j < 8; j++) {
            usuario[j] = 'a' + rand() % 26;
        }
        for(j = 8; j < 11; j++) {
            usuario[j] = '0' + rand() % 10;
        }
        usuario[11] = '\0'; // CORREÇÃO: Garante terminação da string

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

void processarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro) {
    FILE *file = fopen(arq, "r");
    FILE *result = fopen("./testes/resultados/resultados.csv", "a");
    
    if(!file || !result) {
        printf("Nao foi possivel processar o arquivo!\n");
        if(file) fclose(file);
        return; // CORREÇÃO: Removido o "-1" de uma função void
    }

    clock_t t;
    char usuario[12];
    double cpu_time_used, fp;

    fprintf(result, "%d;", num_reg);

    // Teste 1: Busca pura na Hash
    t = clock();
    while(fscanf(file, "%s", usuario) != EOF) { // CORREÇÃO: Loop infinito resolvido com EOF
        buscarHash(tabela, usuario);
    }
    t = clock() - t;
    cpu_time_used = ((double) t) / CLOCKS_PER_SEC;
    fprintf(result, "%f;", cpu_time_used);

    fseek(file, 0, SEEK_SET);

    // Teste 2: Busca Otimizada com o Filtro de Bloom protegendo a Hash
    t = clock();
    while(fscanf(file, "%s", usuario) != EOF) { // CORREÇÃO: Loop infinito resolvido com EOF
        if(consultarBloom(filtro, usuario)) {
            buscarHash(tabela, usuario);
        }
    }
    t = clock() - t;
    cpu_time_used = ((double) t) / CLOCKS_PER_SEC;
    fprintf(result, "%f;", cpu_time_used);

    fclose(file);

    fp = taxaFalsoPositivo(filtro);
    fprintf(result, "%f\n", fp); // Grava a taxa real de falsos positivos capturada

    fclose(result);
    destruirTabela(tabela);
    liberarBloom(filtro);
}