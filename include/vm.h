#ifndef vm_h
#define vm_h

#include "chunk.h"
#include "value.h"
#include <stdint.h>

#define STACK_MAX 256

typedef struct {
    chunk* chunk;
    uint8_t* ip; // instruction pointer, points to next code to be executed
    value* stack;
    value* stack_top; // one past the top element in the stack
    size_t capacity;
    size_t size;
} virtual_machine;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} interpret_result;

void init_vm(virtual_machine* vm);

void free_vm(virtual_machine* vm);

interpret_result interpret(virtual_machine* vm, const char* source);

void push(virtual_machine* vm, value val);

value pop(virtual_machine* vm);

#endif
