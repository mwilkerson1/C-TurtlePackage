CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = $(shell sdl2-config --libs) -lGL -ldl

SRC = ./src/events_handler.c
OBJ = $(SRC:.c=.o)
TARGET = ./Binaries/events_handler 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	
./src/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

