#include "vm.h"
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void reset_stack(virtual_machine* vm) { vm->stack_top = vm->stack; }

void init_vm(virtual_machine* vm)
{
    vm->capacity = 256;
    vm->size = 0;
    vm->stack = malloc(vm->capacity * sizeof(value));
    reset_stack(vm);
}

void free_vm(virtual_machine* vm)
{
    free(vm->stack);
    vm->stack_top = NULL;
    vm->stack = NULL;
    vm->capacity = 0;
    vm->size = 0;
}

void grow_stack(virtual_machine* vm)
{
    vm->capacity *= 2;
    vm->stack = realloc(vm->stack, vm->capacity * sizeof(value));
    vm->stack_top = vm->stack_top + vm->size;
}

void push(virtual_machine* vm, value val)
{
    *vm->stack_top = val;
    vm->stack_top++;
    vm->size++;

    if (vm->size == vm->capacity) {
        grow_stack(vm);
    }
}

value pop(virtual_machine* vm)
{
    if (vm->size == 0) {
        printf("Error: Popped empty stack");
        exit(ERANGE);
    }
    vm->stack_top--;
    vm->size--;
    return *vm->stack_top;
}

static interpret_result run(virtual_machine* vm)
{

#define READ_BYTE(vm) (*(vm->ip++))

#define READ_CONSTANT(vm) (vm->chunk->constants.values[READ_BYTE(vm)])

#define BINARY_OP(vm, op)                                                      \
    do { /* do-while ensures same scope */                                     \
        double b = pop(vm);                                                    \
        double a = pop(vm);                                                    \
        push(vm, a op b);                                                      \
    } while (false)

    while (true) {

#ifdef DEBUG_TRACE_EXECUTION
        // print each value in stack each iteration, for debugging
        printf("    ");
        for (value* slot = vm->stack; slot < vm->stack_top; slot++) {
            printf("[");
            print_value(*slot);
            printf("]");
        }
        printf("\n");
        disassemble_instruction(vm->chunk, (int)(vm->ip - vm->chunk->code));
#endif

        uint8_t instruction = READ_BYTE(vm);
        switch (instruction) {

        case OP_CONSTANT: {
            value constant = READ_CONSTANT(vm);
            push(vm, constant);
            break;
        }

        case OP_ADD:
            BINARY_OP(vm, +);
            break;

        case OP_SUBTRACT:
            BINARY_OP(vm, -);
            break;

        case OP_MULTIPLY:
            BINARY_OP(vm, *);
            break;

        case OP_DIVIDE:
            BINARY_OP(vm, /);
            break;

        case OP_NEGATE:
            *vm->stack_top = -(*vm->stack_top);
            break;

        case OP_RETURN:
            print_value(pop(vm));
            printf("\n");
            return INTERPRET_OK;
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

interpret_result interpret(virtual_machine* vm, const char* source)
{
    compile(source);
    return INTERPRET_OK;
}
