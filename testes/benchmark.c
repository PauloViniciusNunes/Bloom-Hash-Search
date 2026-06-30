#include "benchmark.h"

void inicializar(int n, hashTable **t[], BloomFilter **f[]) {
    for (int i = 0; i < n; i++) {
        *t[i] = criarHash();
        *f[i] = criarBloom();
    }
}

void gerarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro, int mode) {
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

    if(mode == 0) {
        destruirTabela(tabela);
        liberarBloom(filtro);
    }
}

void lerArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro) {
    FILE *file = fopen(arq, "r");
    if(!file) {
        printf("Nao foi possivel abrir o arquivo!\n");
        return;
    }

    char usuario[12];
    int i;
    for(i = 0; i < num_reg; i++) {
        fscanf(file, "%s", usuario);
        inserirHash(tabela, usuario);
        inserirBloom(filtro, usuario);
    }
    fclose(file);
}

void processarArquivo(const char *arq, int num_reg, hashTable *tabela, BloomFilter *filtro) {
    FILE *file = fopen(arq, "r");
    FILE *result = fopen("./testes/resultados/resultados.csv", "a");
    
    if(!file || !result) {
        printf("Nao foi possivel processar o arquivo!\n");
        if(file) fclose(file);
        return;
    }

    clock_t t;
    char usuario[12];
    double cpu_time_used, fp;

    fprintf(result, "%d;", num_reg);

    // Teste 1: Busca pura na Hash
    t = clock();
    while(fscanf(file, "%s", usuario) != EOF) {
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

    fseek(file, 0, SEEK_SET);

    while(fscanf(file, "%s", usuario) != EOF) {
        if(consultarBloom(filtro, usuario)&&(!buscarHash(tabela, usuario))) {
            registrarFalsoPositivo(filtro);
        }
    }

    fclose(file);

    fp = taxaFalsoPositivo(filtro);
    fprintf(result, "%lf\n", fp); // Grava a taxa real de falsos positivos capturada

    printf("----%d registros----\n", num_reg);
    printf("Numero de colisoes na hash: %ld\n", tabela->colisoes);
    printf("taxa de ocupacao: %.2f %%\n", (float)(100*tabela->ocupacao)/N);
    printf("Numero de falsos positivos: %d\n", filtro->falsosPositivos);

    fclose(result);
    destruirTabela(tabela);
    liberarBloom(filtro);
}