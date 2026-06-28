#include "../includes/hash.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// Testa a criação da tabela hash
void testarCriacaoHash(void)
{
    hashTable *tabela = criarHash();

    assert(tabela != NULL);
    // assert é a função para verificar uma condição verdadeira. O programa encerra em caso de false
    assert(tabela->qtd == 0); // Cada função possuirá assert para testes unitários

    for (int i = 0; i < N; i++)
    {
        assert(tabela->hash[i] == NULL);
    }

    destruirTabela(tabela);

    printf("[PASS] testarCriacaoHash\n");
}

//Testa se a função hash é determinística.
void testarGeracaoHash(void)
{
    unsigned int h1 = gerarHash("joao");
    unsigned int h2 = gerarHash("joao");
    unsigned int h3 = gerarHash("maria");

    assert(h1 == h2);
    assert(h1 < N);
    assert(h3 < N);

    printf("[PASS] testarGeracaoHash\n");
}

//Testa a criação de um usuário.
void testarCriacaoUsuario(void)
{
    User *usuario = criarUsuario("paulo");

    assert(usuario != NULL);
    assert(strcmp(usuario->nome, "paulo") == 0);
    assert(usuario->nextUser == NULL);

    free(usuario);

    printf("[PASS] testarCriacaoUsuario\n");
}

//Testar a inserção de um único elemento
void testarInsercao(void)
{
    hashTable *tabela = criarHash();

    inserirHash(tabela, "joao");

    assert(tabela->qtd == 1);

    User *usuario = buscarHash(tabela, "joao");

    assert(usuario != NULL);
    assert(strcmp(usuario->nome, "joao") == 0);

    destruirTabela(tabela);

    printf("[PASS] testarInsercao\n");
}

//testa múltiplas inserções
void testarMultiplasInsercoes(void)
{
    hashTable *tabela = criarHash();

    inserirHash(tabela, "joao");
    inserirHash(tabela, "maria");
    inserirHash(tabela, "pedro");
    inserirHash(tabela, "ana");

    assert(tabela->qtd == 4);

    assert(buscarHash(tabela, "joao") != NULL);
    assert(buscarHash(tabela, "maria") != NULL);
    assert(buscarHash(tabela, "pedro") != NULL);
    assert(buscarHash(tabela, "ana") != NULL);

    destruirTabela(tabela);

    printf("[PASS] testarMultiplasInsercoes\n");
}

//  Testa busca de elemento inexistente

void testarBuscaInexistente(void)
{
    hashTable *tabela = criarHash();

    inserirHash(tabela, "joao");

    assert(buscarHash(tabela, "maria") == NULL);

    destruirTabela(tabela);

    printf("[PASS] testarBuscaInexistente\n");
}

// Procura duas strings que colidam para validar o tratamento de colisões
 
void testarColisao(void)
{
    hashTable *tabela = criarHash();

    char nome1[32];
    char nome2[32];

    int encontrou = 0;

    for (int i = 0; i < 10000 && !encontrou; i++)
    {
        sprintf(nome1, "usuario_%d", i);

        unsigned int hash1 = gerarHash(nome1);

        for (int j = i + 1; j < 10000; j++)
        {
            sprintf(nome2, "usuario_%d", j);

            if (gerarHash(nome2) == hash1)
            {
                encontrou = 1;
                break;
            }
        }
    }

    assert(encontrou);

    inserirHash(tabela, nome1);
    inserirHash(tabela, nome2);

    assert(tabela->qtd == 2);

    assert(buscarHash(tabela, nome1) != NULL);
    assert(buscarHash(tabela, nome2) != NULL);

    destruirTabela(tabela);

    printf("[PASS] testarColisao\n");
}

// Testa a função de remoção de prefixo
void testarRemoverPrefixo(void)
{
    char comando[] = "INSERIR joao";

    char *resultado = removerPrefixo(comando, "INSERIR ");

    assert(strcmp(resultado, "joao") == 0);

    printf("[PASS] testarRemoverPrefixo\n");
}

//Executa todos os testes unitários.
int main(void) 
{
    printf("=========================================\n");
    printf(" TESTES UNITÁRIOS - TABELA HASH\n");
    printf("=========================================\n\n");

    testarCriacaoHash();
    testarGeracaoHash();
    testarCriacaoUsuario();
    testarInsercao();
    testarMultiplasInsercoes();
    testarBuscaInexistente();
    testarColisao();
    testarRemoverPrefixo();

    printf("\n=========================================\n");
    printf("TODOS OS TESTES FORAM APROVADOS!\n");
    printf("=========================================\n");

    return 0;
}

// >:D