#ifndef vm_h
#define vm_h

#include "chunk.h"
#include "value.h"
#include <stdint.h>

#define STACK_MAX 256

typedef struct {
    chunk* chunk;
    uint8_t* ip; // instruction pointer, points to next code to be executed
    value stack[STACK_MAX]; // instruction stack
    value* stack_top;       // one past the top element in the stack
} virtual_machine;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} interpret_result;

void init_vm(void);
void free_vm(void);

interpret_result interpret(chunk* chunk);

void push(value val);
value pop(void);

#endif
