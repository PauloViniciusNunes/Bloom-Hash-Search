# Bloom-Hash-Search
Repositório do trabalho de estruturas de dados II

Sistema de verificação de cadastro de usuários utilizando **Tabela Hash** e **Filtro de Bloom**, desenvolvido em linguagem **C** para a disciplina de **Estruturas de Dados**.

---

# Descrição

O projeto implementa um sistema de cadastro de usuários que combina uma **Tabela Hash** com um **Filtro de Bloom** para otimizar operações de inserção e consulta.

O Filtro de Bloom atua como uma camada de pré-verificação, evitando consultas desnecessárias à Tabela Hash quando é possível determinar que um usuário **certamente não está cadastrado**. Caso o Bloom Filter indique que o usuário **pode existir**, a Tabela Hash realiza a confirmação da consulta.

Além da aplicação principal, o projeto possui módulos destinados à realização de **testes unitários** e **experimentos de desempenho (benchmarks)**.

---

# Funcionalidades

- Cadastro de usuários;
- Consulta de usuários;
- Inserção em lote por meio de arquivos texto;
- Exibição de estatísticas do sistema;
- Testes unitários da Tabela Hash;
- Benchmark para comparação entre buscas utilizando apenas a Tabela Hash e buscas utilizando Bloom Filter + Tabela Hash;
- Geração automática dos resultados experimentais em formato CSV.

---

# Estrutura do Projeto

```text
Bloom-Hash-Search
│
├── data/
│   └── usuarios.txt
│
├── includes/
│   ├── benchmark.h
│   ├── bloom.h
│   ├── hash.h
│   └── usuario.h
│
├── src/
│   ├── bloom.c
│   ├── hash.c
│   ├── main.c
│   ├── teste_hash.c
│   └── usuario.c
│
├── testes/
│   ├── benchmark.c
│   ├── teste.c
│   └── resultados/
│       └── resultados.csv
│
├── .gitignore
├── Makefile
├── README.md
└── Relatorio.pdf
```

---

# Organização dos Módulos

## Hash (`hash.c`)

Responsável pelo armazenamento definitivo dos usuários utilizando uma Tabela Hash com tratamento de colisões por **encadeamento externo**.

### Principais funções

- Criação da tabela Hash;
- Inserção de usuários;
- Busca de usuários;
- Criação de registros;
- Tratamento de colisões;
- Liberação da memória.

---

## Bloom Filter (`bloom.c`)

Implementa o Filtro de Bloom utilizado para reduzir consultas desnecessárias à Tabela Hash.

### Principais funções

- Criação do filtro;
- Inserção de elementos;
- Consulta probabilística;
- Registro de falsos positivos;
- Cálculo da taxa de falsos positivos;
- Liberação da memória.

---

## Usuário (`usuario.c`)

Implementa as operações disponíveis para o usuário da aplicação.

### Principais funções

- Exibição do menu;
- Inserção de usuários;
- Consulta de usuários.

---

## Benchmark (`benchmark.c`)

Responsável pela geração das bases de dados e execução dos experimentos.

Permite:

- Gerar arquivos de teste;
- Carregar arquivos existentes;
- Executar benchmarks;
- Gerar automaticamente um arquivo CSV contendo os resultados.

---

# Funcionamento do Sistema

## Inserção de usuários

1. O Bloom Filter é consultado.
2. Caso indique que o usuário certamente não existe, ele é inserido.
3. Caso indique possível existência, a Tabela Hash confirma essa informação.
4. Se o usuário ainda não existir, ele é inserido:
   - na Tabela Hash;
   - no Bloom Filter;
   - no arquivo `usuarios.txt`.

---

## Consulta de usuários

1. O Bloom Filter é consultado.
2. Caso o filtro indique que o usuário certamente não existe, a busca é encerrada imediatamente.
3. Caso indique possível existência, a Tabela Hash realiza a confirmação.

---

## Estatísticas

O sistema apresenta:

- Total de usuários cadastrados;
- Total de consultas realizadas;
- Consultas descartadas diretamente pelo Bloom Filter;
- Quantidade de falsos positivos;
- Taxa percentual de falsos positivos.

---

## Inserção em lote

O sistema permite importar automaticamente diversos usuários a partir de um arquivo `.txt`, utilizando a mesma lógica de validação empregada na inserção individual.

---

# Compilação

Para compilar a aplicação principal:

```bash
make
```

ou

```bash
make all
```

---

# Executando a Aplicação

Após a compilação:

```bash
./main
```

---

# Compilando os Testes

```bash
make test
```

---

# Executando os Benchmarks

Após compilar os testes:

```bash
./teste <x> <y> <z>
```

Onde:

| Parâmetro | Descrição |
|-----------|-----------|
| `x = 1` | Gera os arquivos utilizados nas buscas |
| `y = 1` | Gera novas bases de dados |
| `y = 0` | Utiliza bases previamente existentes |
| `z = 1` | Executa os experimentos |

### Exemplo

```bash
./teste 1 1 1
```

---

# Resultados

Os resultados dos experimentos são gravados automaticamente em:

```text
testes/resultados/resultados.csv
```

O arquivo gerado possui o seguinte formato:

```csv
Quantidade;Tempo sem Bloom;Tempo com Bloom;Falsos positivos
```

Essas informações permitem comparar o desempenho da busca utilizando apenas a **Tabela Hash** com a abordagem que utiliza o **Filtro de Bloom** como mecanismo de pré-verificação.

---

# Testes Unitários

O projeto possui um conjunto de testes unitários para validar a implementação da Tabela Hash.

Os testes verificam:

- Criação da tabela Hash;
- Funcionamento da função Hash;
- Criação de usuários;
- Inserção de elementos;
- Múltiplas inserções;
- Busca de usuários existentes;
- Busca de usuários inexistentes;
- Tratamento de colisões;
- Remoção de prefixos em comandos.

---

# Tecnologias Utilizadas

- Linguagem C
- GCC
- Makefile

### Bibliotecas

- `stdio.h`
- `stdlib.h`
- `string.h`
- `stdbool.h`
- `time.h`
- `math.h`
- `assert.h`

---

# Autores

Projeto desenvolvido para a disciplina de **Estruturas de Dados**.

---

# Licença

Este projeto possui finalidade exclusivamente acadêmica.