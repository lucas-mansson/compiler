#pragma once

#include <optional>
#include <string>

enum TokenType {
    INTEGER_LITERAL,
    PLUS,
    SEMICOLON,
    EOF_TOKEN,
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::optional<int> value;
};

std::string token_to_string(Token token);
