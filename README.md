# Compiler

The compiler is written in C and compiles to bytecode. The project contains a garbage collector and an emulator/virtual machine that runs the bytecode.

## Things to add:

Features I would like:

- [ ] Differentiate integer and floating point numbers
- [ ] Ternary operator
- [ ] Differentiate const and var
- [ ] private/public data and methods
- [ ] do-while
- [ ] Static type checking
- [ ] arrays and [] operator
- [ ] Add multi-line comments
- [ ] LLVM integration
- [ ] String interpolation
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

### Grammar (outdated)
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

