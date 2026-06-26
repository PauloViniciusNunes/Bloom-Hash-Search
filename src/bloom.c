typedef struct {
    unsigned char *bits;
    int m;
    int k;
    long consultas;
    long consultasEvitadas;
    long falsosPositivos;
} BloomFilter;

// Função hash 1
unsigned int hash1(char *str)
{
    unsigned int hash = 5381;

    while(*str)
        hash = ((hash << 5) + hash) + *str++;

    return hash;
}

// Função hash 2
unsigned int hash2(char *str)
{
    unsigned int hash = 0;

    while(*str)
        hash = hash * 131 + *str++;

    return hash;
}

BloomFilter* criarBloom(int m, int k)
{
    BloomFilter *bf = malloc(sizeof(BloomFilter));

    bf->m = m;
    bf->k = k;
    bf->consultas=0;
    bf->consultasEvitadas=0;
    bf->falsosPositivos=0;

    bf->bits = calloc((m + 7) / 8, sizeof(unsigned char));

    return bf;
}

void inserirBloom(BloomFilter *bf, char *str)
{
    for(int i = 0; i < bf->k; i++)
    {
        int pos = gerarHash(str, i, bf->m);

        bf->bits[pos / 8] |= (1 << (pos % 8));
    }
}

int consultarBloom(BloomFilter *bf, char *str)
{
    for(int i = 0; i < bf->k; i++)
    {
        int pos = gerarHash(str, i, bf->m);

        if(!(bf->bits[pos / 8] & (1 << (pos % 8))))
            return 0;
    }

    return 1;
}

void liberarBloom(BloomFilter *bf)
{
    free(bf->bits);
    free(bf);
}

int consultarSistema(BloomFilter *bf, Hash *hash, char *usuario){
    bf->consultas++;

    if(!consultarBloom(bf,usuario))
    {
        bf->consultasEvitadas++;

        return 0;
    }

    if(buscarHash(hash,usuario))
        return 1;

    bf->falsosPositivos++;

    return 0;
}

double taxaFalsoPositivo(BloomFilter *bf)
{
    if(bf->consultas==0)
        return 0;

    return
        (100.0*bf->falsosPositivos)/
        bf->consultas;
}
