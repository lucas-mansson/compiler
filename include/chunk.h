#ifndef CHUNK_H
#define CHUNK_H
#include "common.h"
#include "value.h"
//
// Keep track of line
typedef struct {
    int count;
    int line;
} line_info;

// Operation codes, what kind of instruction is used
typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} op_code;

typedef struct {
    // Opcodes - dynamic array
    uint8_t* code;
    int count;
    int capacity;

    // Stores pairs [(count1, line1), (count2, line2)]
    // e.g (3, 2) means 3 instructions are on line 2
    line_info* lines;
    int lines_count;
    int lines_capacity;

    value_array constants;
} chunk;

void init_chunk(chunk* chunk);

void write_chunk(chunk* chunk, uint8_t byte, int line);

void free_chunk(chunk* chunk);

int add_constant(chunk* chunk, value val);

// From an instructions index, get the current oine
int get_line(chunk* chunk, int instruction_index);

#endif
