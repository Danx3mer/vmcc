#include "prodRules.hpp"

void ProdRule::updateTokens(std::vector<Token> tokens)
{
    for (Token t : tokens)
        std::cout << t.content;
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
    bool res = true;
    this->statementType = StatementType(Statement::getStatementType(tokens[0]));
    if (this->getType() == UNDEFINED)
        res = false;
    if (res)
        for (Token token : tokens)
        {
            if (&token == &tokens[0])
                continue;
            if (&token == &tokens[tokens.size() - 1])
                if (token.type != SEMICOLON)
                    res = false;
                else if (token.type != DIGIT)
                    res = false;
        }

    if (!res)
        std::cerr << "\nINVALID STATEMENT!!!\n";
    return res;
}

void Statement::addChild(Expression expression)
{
    this->expression = expression;
}

Expression Statement::getChild() { return this->expression; }

Statement::StatementType Statement::getType()
{
    return this->statementType;
}

Statement::StatementType Statement::getStatementType(Token token)
{
    if (token.type != KEYWORD)
        return UNDEFINED;
    if (token.content == "return")
        return RETURN;

    return UNDEFINED;
}

void Statement::prettyPrint()
{
    std::cout << "STATEMENT\nVALID: ";
    std::cout << (this->checkIfValid() ? "TRUE" : "FALSE") << "\nTYPE: ";
    switch (this->statementType)
    {
    case RETURN:
        std::cout << "RETURN";
        break;
    case UNDEFINED:
        std::cout << "UNDEFINED";
        break;
    }
    std::cout << "\n";
}

bool Function::checkIfValid()
{
    for (Statement statement : statements)
        if (!statement.checkIfValid())
            return false;

    if (tokens[0].content != "int")
        return false;

    short i;
    std::string id = "";
    for (i = 1; i < tokens.size(); i++)
    {
        if (tokens[i].content == "(")
            break;
        else if (tokens[i].type == SYMBOL)
            return false;
        else
            id += tokens[i].content;
    }

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

void Function::prettyPrint()
{
    std::cout << "\nFUNCTION\nID: " << this->getFuncID() << "\nNUMBER OF STATEMENTS: " << this->getChildren().size() << "\n";
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
