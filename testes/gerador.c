#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


int buscarRegistro(const char *arq, const char *user) {
    FILE *file = fopen(arq, "r");
    char arq_usuario[12];
    while(fscanf(file, "%s", arq_usuario)) {
        if(strcmp(user, arq_usuario) == 0) {
            return 1;
        }
    }
    return 0;
}
void gerarArquivo(const char *arq, int num_reg) {
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
        fprintf(file, "%s\n", usuario);

        if(buscaRegistro(arq, usuario)) {
            i--;
            continue;
        }
    }
    fclose(file);
}

int main() {
    srand(time(NULL));

    gerarArquivo("registros1000.txt", 1000);
    gerarArquivo("registros10000.txt", 10000);
    gerarArquivo("registros100000.txt", 100000);
    return 0;
}