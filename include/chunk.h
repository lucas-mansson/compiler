#ifndef CHUNK_H
#define CHUNK_H
#include "common.h"

// Operation codes, controls what kind of instruction is used
typedef enum {
    OP_RETURN,
} op_code;

// dynamic array
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} chunk;

void init_chunk(chunk* chunk);

void write_chunk(chunk* chunk, uint8_t byte);

void free_chunk(chunk* chunk);

#endif
