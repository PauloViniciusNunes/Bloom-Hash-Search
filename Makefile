# ==============================
# CONFIGURACOES DO COMPILADOR
# ==============================

CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

# ==============================
# DIRETORIOS
# ==============================

SRC_DIR = src
TEST_DIR = tests

# ==============================
# ARQUIVOS PRINCIPAIS
# ==============================

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/hash.c \
	  $(SRC_DIR)/bloom.c \

# ==============================
# EXECUTAVEL PRINCIPAL
# ==============================

TARGET = hash

# ==============================
# COMPILACAO PRINCIPAL
# ==============================

all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

# ==============================
# EXECUTAR O PROGRAMA
# ==============================

run: all
	./$(TARGET)