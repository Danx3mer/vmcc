#pragma once
#include <iostream>

enum TokenType {
    START,
    DIGIT,
    CHARACTER,
    SYMBOL,
    SEMICOLON,
    KEYWORD,
    UNDEFINED
};

class Token {
    public:
    TokenType type;
    std::string content;

    static TokenType getTokenType(char unLexedToken);

    Token(TokenType type, std::string content): type(type), content(content) {}

    private:
    friend class ParserManager;
    Token() :type(START), content("") {}
};
