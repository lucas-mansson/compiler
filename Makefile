CC = gcc
CFLAGS = -g -Iinclude -Wall -Wextra -Wpedantic -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = build/main

.PHONY: all clean run test

all: $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: build $(TARGET)
	@./$(TARGET) $(ARGS)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

clean:
	rm -rf build/

test: $(TARGET)
	./test/test.sh $(TARGET)

check: build $(TARGET)
	valgrind $(TARGET)
