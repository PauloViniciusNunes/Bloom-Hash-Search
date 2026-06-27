#include "../includes/hash.h"

unsigned int gerarHash(char *nome)
{
    unsigned int hash = 5381;

    while (*nome)
        hash = ((hash << 5) + hash) + (unsigned char)*nome++;

    return hash % N;
}

char *removerPrefixo(char *str, const char *prefixo)
{
    size_t tam = strlen(prefixo);

    if (strncmp(str, prefixo, tam) == 0)
        return str + tam;

    return str;
}

User* criarUsuario(char* nome)
{
    User* novo = (User*)malloc(sizeof(User));

    if(!novo)
    {
        return NULL;
    }

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->nextUser = NULL;
    return novo;
}

void inserirUsuario(char *nome, Hash tabela)
{
    unsigned int idx = gerarHash(nome);

    User *novo = criarUsuario(nome);

    if (novo == NULL)
    {
        printf("\n[ERRO] Falha na alocação.\n\n");
        return;
    }

    novo->nextUser = tabela[idx];
    tabela[idx] = novo;

    printf("→ Usuario adicionado.\n");
}

User *buscarUsuario(char *nome, Hash tabela)
{
    unsigned int idx = gerarHash(nome);

    User *consultado = tabela[idx];

    while (consultado != NULL)
    {
        if (strcmp(consultado->nome, nome) == 0)
        {   
            printf("→ Usuario encontrado.\n");
            return consultado;
        }

        consultado = consultado->nextUser;
    }

    printf("→ Usuario não encontrado.\n");
    return NULL;
}

void destruirTabela(Hash tabela)
{
    for (int i = 0; i < N; i++)
    {
        User *p = tabela[i];

        while (p)
        {
            User *aux = p;
            p = p->nextUser;
            free(aux);
        }
    }
}

void interpretarComando(char* comando, Hash tabela)
{

    if(strstr(comando, "INSERIR") != NULL)
    {
        char *nome = removerPrefixo(comando, "INSERIR ");
        inserirUsuario(nome, tabela);
    }
    else if(strstr(comando, "CONSULTAR") != NULL)
    {
        char *nome = removerPrefixo(comando, "CONSULTAR ");
        buscarUsuario(nome, tabela);
    }
    else if(strstr(comando,"DELETAR") != NULL)
    {
        char *nome = removerPrefixo(comando, "DELETAR ");
        deletarUsuario(nome, tabela);
    }
    else if(strstr(comando, "SAIR") != NULL)
    {
        destruirTabela(tabela);
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("\n[ERROR] COMANDO DESCONHECIDO.\n\n");
    }
}

void deletarUsuario(char *nome, Hash tabela)
{
    unsigned int idx = gerarHash(nome);

    User *atual = tabela[idx];
    User *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            /* Remoção do primeiro nó da lista */
            if (anterior == NULL)
            {
                tabela[idx] = atual->nextUser;
            }
            /* Remoção de um nó no meio ou no final */
            else
            {
                anterior->nextUser = atual->nextUser;
            }

            free(atual);
            printf("→ Usuario deletado.\n");
            return;
        }

        anterior = atual;
        atual = atual->nextUser;
    }

    printf("→ Usuario não encontrado.\n");
}


// ---- MAIN SECTION ---- //
int main()
{
    Hash t;

    while(true)
    {
        char comando[100];
        printf("DIGITE O COMANDO: ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = '\0';
        interpretarComando(comando, t);
    }
}