#ifndef vm_h
#define vm_h

#include "chunk.h"
#include <stdint.h>

typedef struct {
    chunk* chunk;
    uint8_t* ip; // instruction pointer
} virtual_machine;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} interpret_result;

void init_vm();
void free_vm();

interpret_result interpret(chunk* chunk);

#endif
