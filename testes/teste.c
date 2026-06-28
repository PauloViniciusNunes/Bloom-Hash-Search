#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hash.h"
#include "bloom.h"

int main() {
    srand(time(NULL));

    FILE *file = fopen("./resultados/resultados", "a");
    fprintf(file, "Quantidade;Tempo sem Bloom;Tempo com Bloom;Falsos positivos\n");
    fclose(file);

    hashTable *tabela = criarHash();
    bloomfilter *filtro = criarBloom();
    gerarArquivo("registros1000.txt", 1000, tabela, filtro);
    processarArquivo("registros1000.txt", 1000, tabela, filtro);

    tabela = criarHash();
    filtro = criarBloom();
    gerarArquivo("registros1000.txt", 10000, tabela, filtro);
    processarArquivo("registros1000.txt", 10000, tabela, filtro);

    tabela = criarHash();
    filtro = criarBloom();
    gerarArquivo("registros1000.txt", 100000, tabela, filtro);
    processarArquivo("registros1000.txt", 100000, tabela, filtro);
    return 0;
}