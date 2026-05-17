#include "chunk.h"
#include "memory.h"
#include "pair.h"
#include "value.h"
#include <stdlib.h>

void init_chunk(chunk* chunk)
{
    chunk->code = NULL;
    chunk->count = 0;
    chunk->capacity = 0;

    chunk->lines = NULL;
    chunk->lines_count = 0;
    chunk->lines_capacity = 0;

    init_value_array(&chunk->constants);
}

void write_chunk(chunk* chunk, uint8_t byte, int line)
{
    // Chunk code
    if (chunk->capacity == chunk->count) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;

    // Line info
    if (chunk->lines_count > 0 &&
        chunk->lines[chunk->lines_count - 1].line == line) {
        chunk->lines[chunk->lines_count - 1]
            .count++; // If we are on the same line, increment
    } else {
        // new line, check if we need to allocate new memory
        if (chunk->lines_count == chunk->lines_capacity) {
            int old_capacity = chunk->lines_capacity;
            chunk->lines_capacity = GROW_CAPACITY(old_capacity);
            chunk->lines = GROW_ARRAY(line_info, chunk->lines, old_capacity,
                                      chunk->lines_capacity);
        }
        line_info l;
        l.count = 1;   // initial count
        l.line = line; // line number
        chunk->lines[chunk->lines_count] = l;
        chunk->lines_count++;
    }
}

void free_chunk(chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(line_info, chunk->lines, chunk->lines_capacity);
    free_value_array(&chunk->constants);
}

int add_constant(chunk* chunk, value val)
{
    write_value_array(&chunk->constants, val);
    return chunk->constants.count - 1;
}

int get_line(chunk* chunk, int instruction_index)
{
    int curr_offset = 0;
    for (int i = 0; i < chunk->lines_count; i++) {
        line_info curr_line = chunk->lines[i];
        curr_offset += curr_line.count;
        if (instruction_index < curr_offset) {
            return curr_line.line;
        }
    }

    return -1;
}
