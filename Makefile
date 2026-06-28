# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Iincludes

# Diretórios
SRC_DIR = src
TEST_DIR = testes

# Arquivos da aplicação principal
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/hash.c \
	$(SRC_DIR)/bloom.c

# Arquivos do benchmark
TEST_SRC = \
	$(TEST_DIR)/teste.c \
	$(TEST_DIR)/benchmark.c \
	$(SRC_DIR)/hash.c \
	$(SRC_DIR)/bloom.c

# Executáveis
TARGET = main
TEST_TARGET = teste

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)