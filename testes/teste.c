#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../includes/hash.h"
#include "../includes/bloom.h"
#include "../includes/benchmark.h"

int main() {
    srand(time(NULL));

    FILE *file = fopen("./testes/resultados/resultados.csv", "w");
    if (file) {
        fprintf(file, "Quantidade;Tempo sem Bloom;Tempo com Bloom;Falsos positivos\n");
        fclose(file);
    }

    // Instanciação 1: 1.000 Registros
    hashTable *t1 = criarHash();
    BloomFilter *f1 = criarBloom();
    gerarArquivo("registros1000.txt", 1000, t1, f1);
    processarArquivo("registros1000.txt", 1000, t1, f1);

    // Instanciação 2: 10.000 Registros
    hashTable *t2 = criarHash();
    BloomFilter *f2 = criarBloom();
    gerarArquivo("registros10000.txt", 10000, t2, f2);
    processarArquivo("registros10000.txt", 10000, t2, f2);

    // Instanciação 3: 100.000 Registros
    hashTable *t3 = criarHash();
    BloomFilter *f3 = criarBloom();
    gerarArquivo("registros100000.txt", 100000, t3, f3);
    processarArquivo("registros100000.txt", 100000, t3, f3);

    printf("\n[SUCESSO] Testes executados! Os resultados foram consolidados em: ./testes/resultados/resultados.csv\n");
    return 0;
}