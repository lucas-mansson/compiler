#ifndef CHUNK_H
#define CHUNK_H
#include "common.h"
#include "value.h"

// Operation codes, controls what kind of instruction is used
typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} op_code;

// dynamic array
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    value_array constants;
} chunk;

void init_chunk(chunk* chunk);

void write_chunk(chunk* chunk, uint8_t byte);

void free_chunk(chunk* chunk);

int add_constant(chunk* chunk, value val);

#endif
