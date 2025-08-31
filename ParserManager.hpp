#pragma once
#include "prodRules.hpp"

class ParserManager
{
public:
    enum ParsingScope
    {
        PROGRAM,
        FUNCTION,
        STATEMENT,
        EXPRESSION
    };

    ParserManager(std::vector<Token> tokens);

    void exitScope();
    void enterScope();

    // Current Parsing Stuff Getters
    ParsingScope getCurrentScope() { return this->scope; }
    std::vector<Token> getCurrentContent() { return *this->currentContent; }

    void pushToken(Token token);
    void popLastToken();

    void prettyPrint();

    Program getProgram();

private:
    ParsingScope scope;

    std::vector<Token> *currentContent;
    std::vector<std::vector<Token>> content;

    Program currentProgram;
    Function currentFunction;
    Statement currentStatement;
    Expression currentExpression;

    void selectAppropriateContent();
};