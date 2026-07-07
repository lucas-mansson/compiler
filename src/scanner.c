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

static bool is_digit(const char c) { return c >= '0' && c <= '9'; }

static bool is_at_end(void) { return *scan.curr == '\0'; }

static char advance(void) { return *scan.curr++; }

static char peek(void) { return *scan.curr; }

static char peek_next(void)
{
    if (is_at_end()) {
        return '\0';
    }
    return *(scan.curr + 1);
}

static bool match(char expected)
{
    if (is_at_end()) {
        return false;
    }
    if (*scan.curr != expected) {
        return false;
    }

    scan.curr++;
    return true;
}

static void skip_whitespace(void)
{
    while (true) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            scan.line++;
            advance();
            break;

            // comments
        case '/':
            char next = peek_next();
            if (next == '/') {
                while (peek() != '\n' && !is_at_end()) {
                    advance();
                }
            } else if (next == '*') { // multi-line comment
                while (!is_at_end()) {
                    advance();

                    if (peek() == '\n') {
                        scan.line++;
                    }

                    if (peek() == '*' && peek_next() == '/') {
                        advance();
                        advance();
                        return;
                    }
                }

                if (is_at_end()) {
                    return;
                }

            } else {
                return;
            }

        default:
            return;
        }
    }
}

static token string(void)
{
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') {
            scan.line++;
        }
        advance();
    }

    if (is_at_end()) {
        return error_token("Unterminated string");
    }

    advance(); // closing quote

    return make_token(TOKEN_STRING);
}

static token number(void)
{
    while (is_digit(peek())) {
        advance();
    }

    if (peek() == '.' && is_digit(peek_next())) {
        advance(); // consume dot

        while (is_digit(peek())) {
            advance();
        }
    }

    return make_token(TOKEN_NUMBER);
}

token scan_token(void)
{
    scan.start = scan.curr;
    if (is_at_end()) {
        return make_token(TOKEN_EOF);
    }

    char c = advance();

    switch (c) {
        if (is_digit(c)) {
            return number();
        }
    case '(':
        return make_token(TOKEN_LEFT_PAREN);
    case ')':
        return make_token(TOKEN_RIGHT_PAREN);
    case '{':
        return make_token(TOKEN_LEFT_BRACE);
    case '}':
        return make_token(TOKEN_RIGHT_BRACE);
    case ';':
        return make_token(TOKEN_SEMICOLON);
    case ',':
        return make_token(TOKEN_COMMA);
    case '.':
        return make_token(TOKEN_DOT);
    case '-':
        return make_token(TOKEN_MINUS);
    case '+':
        return make_token(TOKEN_PLUS);
    case '/':
        return make_token(TOKEN_SLASH);
    case '*':
        return make_token(TOKEN_STAR);

    case '!':
        return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '>':
        return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '<':
        return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);

    case '"':
        return string();
    }

    return error_token("Unexpected character");
}
