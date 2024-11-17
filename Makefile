CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = $(shell sdl2-config --libs) -lGL -ldl -lm

SRC = ./src/mega.c
OBJ = $(SRC:.c=.o)
TARGET = ./Binaries/turtle 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

./src/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

