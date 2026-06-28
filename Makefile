SRC = $(SRC_DIR)/main.c $(SRC_DIR)/hash.c $(SRC_DIR)/bloom.c
TEST_SRC = testes/teste_perf.c testes/benchmark.c $(SRC_DIR)/hash.c $(SRC_DIR)/bloom.c

all:
	gcc $(SRC) -Wall -Wextra -Iincludes -o hash

test:
	@mkdir -p testes/resultados
	gcc $(TEST_SRC) -Wall -Wextra -Iincludes -o benchmark_test