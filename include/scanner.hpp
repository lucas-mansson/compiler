#pragma once

#include "token.hpp"
#include <vector>

class Scanner
{
  public:
    Scanner(std::string source);
    std::vector<Token> getTokens();

  private:
    std::string source;
    std::vector<Token> tokens;
    size_t position;

    // Adds single-char non-value token
    void add_token(TokenType token_type, char c);

    // Add multi-char token
    void add_token(TokenType token_type, std::string str);

    void add_integer(TokenType token_type, std::string str);

    char peek();

    void number();

    bool is_at_eof();
    bool is_alphabetic(const char c);
    bool is_numeric(const char c);
    bool is_whitespace(const char c);
};
