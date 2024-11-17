# Compiler and flags
CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = -lSDL2 -lGL -lGLU -ldl -lm

# Directories
SRC_DIR = src
BIN_DIR = Binaries

# Source and output files
SRC = $(SRC_DIR)/mega.c
OBJ = $(SRC_DIR)/mega.o
OUT = $(BIN_DIR)/turtle

# Targets
all: $(OUT)

$(OUT): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

$(OBJ): $(SRC)
	@mkdir -p $(SRC_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: all clean
