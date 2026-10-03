
#include "scanner.hpp"
#include "token.hpp"
#include <cctype>
#include <optional>
#include <print>
#include <string>
#include <vector>

Scanner::Scanner(std::string source) : source(std::move(source)), position(0) {}

std::vector<Token> Scanner::getTokens()
{
    while (!is_at_eof()) {
        char c = source[position];
        switch (c) {
        case ';':
            add_token(SEMICOLON, c);
            break;
        case '+':
            add_token(PLUS, c);
            break;
        default:
            if (is_whitespace(c)) {
                break;
            }

            if (is_numeric(c)) {
                add_integer(INTEGER_LITERAL, c);
                break;
            }
            std::println("Error: unexpected character {}", c);
            exit(1);
        }
        position++;
    }

    return tokens;
}

void Scanner::add_token(TokenType token_type, char c)
{
    std::string lexeme(1, c);
    Token token = {
        .type = token_type,
        .lexeme = lexeme,
        .value = std::nullopt,
    };
    tokens.push_back(token);
}

void Scanner::add_integer(TokenType token_type, char c)
{
    std::string lexeme(1, c);

    int value = c - '0';

    Token token = {
        .type = token_type,
        .lexeme = lexeme,
        .value = value,
    };
    tokens.push_back(token);
}

bool Scanner::is_at_eof() { return position >= source.length(); }

bool Scanner::is_alphabetic(const char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Scanner::is_numeric(char c) { return (c >= '0' && c <= '9'); }

bool Scanner::is_whitespace(char c)
{
    std::vector<char> whitespace_chars = {
        ' ',
        '\r',
        '\n',
        '\t',
    };

    for (const auto ws : whitespace_chars) {
        if (c == ws) {
            return true;
        }
    }
    return false;
}
