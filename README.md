# Compiler

This is the code for a interpreted programming language based on the book ["Crating interpreters" by Robert Nystrom.](https://craftinginterpreters.com/). 

The compiler is written in C and compiles to bytecode. The project contains a garbage collector and an emulator/virtual machine that runs the bytecode.

## Things to add:

Features I would like that are not in the book:

- [ ] Differentiate integer and floating point numbers
- [ ] Ternary operator
- [ ] Differentiate const and var
- [ ] private/public data and methods
- [ ] do-while
- [ ] Static type checking
- [ ] arrays and [] operator
- [ ] Add multi-line comments
- [ ] ...

### Standard library

The language has no Standard Library basically. Here are some things to add:

- [ ] Print function
- [ ] Read from command line
- [ ] File I/O
- [ ] Networking
- [ ] ...

## Language specification

### Primitive types

- Booleans
- Numbers (double-precision floating point)
- Strings
- null

### Grammar
```
**Statements**

program     -> declaration* EOF ;

declaration -> stmt 
               | varDecl;

stmt        -> exprStmt 
               | ifStmt
               | printStmt 
               | block ;

varDecl     -> "var" ID ( "=" expr )? ";" ;

ifStmt      -> "if" "(" expr ")" stmt ( "else" stmt )? ;

exprStmt    -> expr ";" ;

printStmt   -> "print" expr ";" ;

block       -> "{" declaration "}"

**Expressions**

expr        -> assignment ("," assignment)* ;

assignment  -> conditional
               | ID "=" assignment ;

conditional -> equality 
            | equality "?" expr ":" expr;

equality    -> comparison ( ( "!=" | "==" ) comparison )* ;

comparison  -> term ( ( ">" | ">=" | "<" | "<=" ) term )* ;

term        -> factor ( ( "-" | "+" ) ) factor)* ;

factor      -> unary ( ( "/" | "*" ) unary )* ;

unary       -> ( "!" | "-" ) unary 
               | primary ;

primary     -> NUMBER 
               | STRING 
               | "true" 
               | "false" 
               | "null" 
               | "(" expression ")" 
               | ID ;
```

### Tokens

The language has the following tokens:
```c
    // Single character tokens
    LPAREN, // "("
    RPAREN, // ")"
    LBRACE, // "{"
    RBRACE, // "}"
    COMMA, // ","
    DOT, // "."
    MINUS, // "-"
    PLUS, // "+"
    SEMICOL, // ";"
    SLASH, // "/"
    STAR, // "*"
    COLON, // ":"

    // Comparison operators
    BANG, // "!"
    BANG_EQ, // "!="
    EQ, // "="
    EQ_EQ, // "=="
    GT, // ">"
    GE, // ">="
    LT, // "<"
    LE, // "<="
    AND, // "&&"
    OR, // "||"

    // Literals
    ID,
    STRING,
    NUMBER,

    // Keywords
    VAR, // "var"
    IF, // "if"
    ELSE, // "else"
    FOR, // "for"
    WHILE, // "while"
    FALSE, // "false"
    TRUE, // "true"
    FUN, // "fun"
    RETURN, // "return"
    NULL, // "null"
    CLASS, // "class"
    THIS, // "this"
    SUPER, // "super"
    PRINT, // "print"
```

