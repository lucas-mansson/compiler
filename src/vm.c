#include "vm.h"
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include <stdio.h>

virtual_machine vm;

void reset_stack(void) { vm.stack_top = vm.stack; }

void init_vm(void) { reset_stack(); }

void free_vm(void) {}

void push(value val)
{
    *vm.stack_top++ = val;
    vm.stack_top++;
}

value pop(void)
{
    vm.stack_top--;
    return *vm.stack_top;
}

static interpret_result run(void)
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    while (true) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("    ");
        // print each value in stack each iteration
        for (value* slot = vm.stack; slot < vm.stack_top; slot++) {
            printf("[");
            print_value(*slot);
            printf("]");
        }
        printf("\n");
        disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction = READ_BYTE();
        switch (instruction) {

        case OP_CONSTANT: {
            value constant = READ_CONSTANT();
            push(constant);
            break;
        }

        case OP_RETURN: {
            print_value(pop());
            printf("\n");
            return INTERPRET_OK;
        }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
}

interpret_result interpret(chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
