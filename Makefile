# Compiler and flags
CC = gcc
CFLAGS = -I./Include -Wall -O2
LDFLAGS = -lSDL2 -lSDL2_image -lGL -lGLU -ldl -lm -lSDL2_ttf

# Directories
SRC_DIR = Src
BIN_DIR = Binaries
OBJ_DIR = Obj

# Source files
SRCS = main.c graphics.c events.c sprite.c text.c utilities.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output binary
OUT = $(BIN_DIR)/turtle

# Targets
all: $(OUT)

$(OUT): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(OUT) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OUT)

.PHONY: all clean
