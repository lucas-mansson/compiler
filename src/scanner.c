#include "scanner.h"
#include <stdbool.h>
#include <string.h>

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

static bool is_at_end(void) { return *scan.curr == '\0'; }

static token make_token(token_type type)
{
    token t;
    t.type = type;
    t.start = scan.start;
    t.length = (scan.curr - scan.start);
    t.line = scan.line;

    return t;
}

static token error_token(const char* msg)
{
    token t;
    t.type = TOKEN_ERROR;
    t.start = msg;
    t.length = strlen(msg);
    t.line = scan.line;

    return t;
}

token scan_token(void)
{
    scan.start = scan.curr;
    if (is_at_end()) {
        return make_token(TOKEN_EOF);
    }

    return error_token("Unexpected character");
}
