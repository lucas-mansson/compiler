#include "scanner.h"
#include <stdbool.h>
#include <stdio.h>

void compile(const char* source)
{
    init_scanner(source);
    int line = -1;

    while (true) {
        token t = scan_token();

        if (t.line != line) {
            printf("%4d", t.line);
            line = t.line;
        } else {
            printf("    | ");
        }
        printf("%2d '%.*s'\n", t.type, t.length, t.start);

        if (t.type == TOKEN_EOF) {
            break;
        }
    }
}
