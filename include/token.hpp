#pragma once

#include <optional>
#include <string>

enum TokenType {
    INTEGER_LITERAL,
    PLUS,
    SEMICOLON,
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::optional<int> value;
};
