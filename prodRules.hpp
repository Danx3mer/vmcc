#pragma once
#include "tokenTypes.hpp"
#include <vector>

class ProdRule
{
public:
    virtual bool checkIfValid() = 0;
    void updateTokens(std::vector<Token> tokens);

    virtual ~ProdRule() = default;

protected:
    std::vector<Token> tokens;
};

class Expression : public ProdRule
{
public:
    Expression() {}
    ~Expression() {}
    Expression(std::vector<Token> tokens);
    bool checkIfValid() override;
    std::string getValue();

    private:
    std::string value;
};

class Statement : public ProdRule
{
public:
    enum StatementType
    {
        RETURN,
        UNDEFINED
    };

    bool checkIfValid() override;

    Statement() {}
    ~Statement() {}

    void addChild(Expression expression);
    Expression getChild();
    StatementType getType();

    void prettyPrint();

private:
    static StatementType getStatementType(Token token);

    Expression expression;
    StatementType statementType;
};

class Function : public ProdRule
{
public:
    bool checkIfValid() override;

    Function() {}
    ~Function() {}

    void addChild(Statement statement);
    std::vector<Statement> getChildren();
    std::string getFuncID();

    void prettyPrint();

private:
    std::string id;
    std::vector<Statement> statements;
};

class Program : public ProdRule
{
public:
    bool checkIfValid() override;

    Program() {}
    ~Program() {}

    void addChild(Function function);
    std::vector<Function> getChildren();

private:
    std::vector<Function> functions;
};