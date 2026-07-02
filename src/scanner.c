#include "scanner.h"

typedef struct {
    const char* start; // start of current lexeme
    const char* curr;  // current character
    int line;
} scanner;

scanner scan;

void init_scanner(const char* source)
{
    scan.start = source;
    scan.curr = source;
    scan.line = 1;
}
