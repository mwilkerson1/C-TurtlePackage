CC = gcc
CFLAGS = -I./include -Wall -O2 -DTEST_HANDLER
LDFLAGS = $(shell sdl2-config --libs) -lGL -ldl -lm

SRC = ./src/events_handler.c ./src/sprite_logic.c ./src/load_sprite.c
OBJ = $(SRC:.c=.o)
TARGET = ./Binaries/test_handler 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

./src/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

