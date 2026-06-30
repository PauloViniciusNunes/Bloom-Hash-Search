#include "benchmark.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if(argc < 4) {
        printf("O numero de parametros para a execucao do teste não e suficiente!\n");
        return -1;
    } 

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int z = atoi(argv[3]);

    FILE *file = fopen("./testes/resultados/resultados.csv", "w");
    if (file) {
        fprintf(file, "Quantidade;Tempo sem Bloom;Tempo com Bloom;Falsos positivos\n");
        fclose(file);
    }

    hashTable *t1 = NULL, *t2 = NULL, *t3 = NULL;
    hashTable **t[] = {&t1, &t2, &t3};
    BloomFilter *f1 = NULL, *f2 = NULL, *f3 = NULL;
    BloomFilter **f[] = {&f1, &f2, &f3};


    if(x == 1) {
        inicializar(3, t, f);
        gerarArquivo("registros1000_busca.txt", 1000, t1, f1, 0);
        gerarArquivo("registros10000_busca.txt", 10000, t2, f2, 0);
        gerarArquivo("registros100000_busca.txt", 100000, t3, f3, 0);
    }

    if(y == 1) {
        inicializar(3, t, f);
        gerarArquivo("registros1000.txt", 1000, t1, f1, 1);
        gerarArquivo("registros10000.txt", 10000, t2, f2, 1);
        gerarArquivo("registros100000.txt", 100000, t3, f3, 1);
    } else {
        inicializar(3, t, f);
        lerArquivo("registros1000.txt", 1000, t1, f1);
        lerArquivo("registros10000.txt", 10000, t2, f2);
        lerArquivo("registros100000.txt", 100000, t3, f3);
    }

    if(z == 1) {
        // Instanciação 1: 1.000 Registros
        processarArquivo("registros1000_busca.txt", 1000, t1, f1);

        // Instanciação 2: 10.000 Registros
        processarArquivo("registros10000_busca.txt", 10000, t2, f2);

        // Instanciação 3: 100.000 Registros
        processarArquivo("registros100000_busca.txt", 100000, t3, f3);
    }

    if(x != 1 && y != 1 && z != 1) {
        printf("Nenhum teste foi realizado!\n");
        return -1;
    }

    printf("\n[SUCESSO] Testes executados! Os resultados foram consolidados em: ./testes/resultados/resultados.csv\n");
    return 0;
}