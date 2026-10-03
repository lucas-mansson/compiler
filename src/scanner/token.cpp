
#include "token.hpp"
#include <print>
#include <string>

std::string token_to_string(Token token)
{
    switch (token.type) {
    case INTEGER_LITERAL:
        return "INTEGER_LITERAL(" + token.lexeme + ")";
    case PLUS:
        return "PLUS(+)";
    case SEMICOLON:
        return "SEMICOLON(;)";
    default:
        std::println(
            "Error converting token type to string: Unknown token type");
        exit(1);
    }
}
