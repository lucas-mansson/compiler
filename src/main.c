#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

static char* read_file(const char* path)
{
    FILE* file = fopen(path, "rb"); // rb == read binary
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\"\n", path);
        exit(EX_IOERR);
    }

    // We need to allocate a string for the entire file, but we dont know how
    // big it is until we read it
    // To fix this, we "seek" (read) until the end of the file
    fseek(file, 0L, SEEK_END);

    // ftell tells us how many bytes we are from the start of the file
    size_t file_size = ftell(file);
    // Go back to beginning of file so we can read it
    rewind(file);

    // allocate space and read the file
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
        exit(EX_IOERR);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\"\n", path);
        exit(EX_IOERR);
    }

    buffer[bytes_read] = '\0';

    fclose(file);

    return buffer;
}

static void run_file(virtual_machine* vm, const char* path)
{
    char* source = read_file(path);
    interpret_result result = interpret(vm, source);
    free(source);
    source = NULL;

    if (result == INTERPRET_COMPILE_ERROR) {
        exit(EX_USAGE);
    }
    if (result == INTERPRET_RUNTIME_ERROR) {
        exit(EX_SOFTWARE);
    }
}

static void repl(virtual_machine* vm)
{
    char line[1024];
    while (true) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        interpret(vm, line);
    }
}

int main(int argc, const char* argv[])
{
    virtual_machine vm;
    init_vm(&vm);

    if (argc == 1) {
        repl(&vm);
    } else if (argc == 2) {
        run_file(&vm, argv[1]);
    } else {
        fprintf(stderr, "Usage build/main [path]");
        exit(EX_USAGE);
    }

    return 0;
}
