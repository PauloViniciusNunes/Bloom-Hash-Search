#ifndef BLOOM_H
#define BLOOM_H

typedef struct{

    unsigned char *bits;

    int tamanhoVetor;

    int quantidadeHashes;

    long consultas;

    long consultasEvitadas;

    long falsosPositivos;

} BloomFilter;


/* Cria o Bloom */
BloomFilter* criarBloom(int tamanhoVetor, int quantidadeHashes);


/* Inserir usuário no filtro de Bloom */
void inserirBloom(BloomFilter *bf, char *usuario);


/* Consulta um usuário no filtro de Bloom */
int consultarBloom(BloomFilter *bf, char *usuario);


/* Calcular a taxa de falsos positivos */
double taxaFalsoPositivo(BloomFilter *bf);


/* Liberar memória */
void liberarBloom(BloomFilter *bf);

#endif