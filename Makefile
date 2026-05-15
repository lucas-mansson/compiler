CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Wpedantic -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/main

.PHONY: all clean run test

all: $(TARGET)

run: $(TARGET)
	@./$(TARGET) $(ARGS)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/

test: $(TARGET)
	./test/test.sh $(TARGET)
