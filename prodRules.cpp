#include "prodRules.hpp"

void ProdRule::updateTokens(std::vector<Token> tokens)
{
    this->tokens = tokens;
}

Expression::Expression(std::vector<Token> &tokens)
{
    this->tokens = tokens;
}

bool Expression::checkIfValid()
{
    for (Token token : tokens)
    {
        if (token.type != DIGIT)
            return false;
    }
    return true;
}

bool Statement::checkIfValid()
{
    bool res=true;
    if (tokens[0].content != "return") res = false;
    if(res)
    for (Token token : tokens)
    {
        if (&token == &tokens[0])
            continue;
        if (&token == &tokens[tokens.size()-1])
            if(token.type!=SEMICOLON) res = false;
        else if (token.type != DIGIT)
            res = false;
    }

    if(!res) std::cerr << "\nINVALID STATEMENT!!!\n";
    else std::cout << "\nVALID STATEMENT\n";
    return res;
}

void Statement::addChild(Expression expression)
{
    this->expression = expression;
}

Expression Statement::getChild() { return this->expression; }

bool Function::checkIfValid()
{
    for (Statement statement : statements)
        if (!statement.checkIfValid())
            return false;

    for(Token t: this->tokens)
        std::cout << t.content;

    if (tokens[0].content != "int")
        return false;

    short i;
    std::string id="";
    for (i = 1; i < tokens.size(); i++)
    {
        if (tokens[i].content == "(")
            break;
        else if (tokens[i].type == SYMBOL)
            return false;
        else
            id += tokens[i].content;
    }

    std::cout << "\nID FOUND: " + id + "\n";

    if (tokens[i + 1].content != ")" || tokens[i + 2].content != "{" || tokens[tokens.size() - 1].content != "}")
        return false;

    this->id = id;

    return true;
}

void Function::addChild(Statement statement)
{
    this->statements.push_back(statement);
}

std::vector<Statement> Function::getChildren() { return this->statements; }

std::string Function::getFuncID()
{
    return (this->checkIfValid()) ? id : "INVALID";
}

bool Program::checkIfValid()
{
    for (Function foo : functions)
        if (!foo.checkIfValid())
            return false;
    return functions.size() > 0;
}

void Program::addChild(Function function)
{
    this->functions.push_back(function);
}

std::vector<Function> Program::getChildren() { return this->functions; }
