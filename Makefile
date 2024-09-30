CC = gcc
CFLAGS = -I./include -Wall -O2
LDFLAGS = $(shell sdl2-config --libs) -lGL -ldl

SRC = src/hello_window.c
OBJ = $(SRC:.c=.o)
TARGET = hello_window 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

