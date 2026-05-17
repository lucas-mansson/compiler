#ifndef CHUNK_H
#define CHUNK_H
#include "common.h"
#include "value.h"

// Operation codes, controls what kind of instruction is used
typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} op_code;

typedef struct {
    int count;
    int capacity;
    uint8_t* code; // Opcodes
    int* lines;    // For error messages
    value_array constants;
} chunk;

void init_chunk(chunk* chunk);

void write_chunk(chunk* chunk, uint8_t byte, int line);

void free_chunk(chunk* chunk);

int add_constant(chunk* chunk, value val);

#endif
