#include "ParserManager.hpp"

ParserManager::ParserManager(std::vector<Token> tokens) : content(4), scope(PROGRAM)
{
    this->currentProgram.updateTokens(tokens);
}

void ParserManager::exitScope()
{
    switch (this->scope)
    {
    case FUNCTION:
    {
        this->currentFunction.updateTokens(*this->currentContent);
        this->currentProgram.addChild(this->currentFunction);
    }
    break;
    case STATEMENT:
    {
        this->currentStatement.updateTokens(*this->currentContent);
        this->currentFunction.addChild(this->currentStatement);
    }
    break;
    case EXPRESSION:
    {
        this->currentExpression = Expression(*this->currentContent);
        this->currentStatement.addChild(this->currentExpression);
    }
    break;
    }

    this->scope = ParsingScope(this->scope - 1);
    this->currentContent->assign({});
    this->selectAppropriateContent();
}

void ParserManager::enterScope()
{
    Token lastToken;
    if (!this->currentContent->empty())
        lastToken = (*this->currentContent)[this->currentContent->size() - 1];
    this->scope = ParsingScope(this->scope + 1);
    this->selectAppropriateContent();
    if (lastToken.type == KEYWORD && this->scope == FUNCTION)
        this->currentContent->push_back(lastToken);
}

void ParserManager::pushToken(Token token)
{
    this->selectAppropriateContent();
    this->currentContent->push_back(token);
}

void ParserManager::popLastToken()
{
    this->currentContent->pop_back();
}

void ParserManager::prettyPrint()
{
    std::cout << "\nPROGRAM\nNUMBER OF FUNCTIONS: " + this->currentProgram.getChildren().size();
    for (Function foo : this->currentProgram.getChildren())
    {
        foo.prettyPrint();
        for (Statement statement : foo.getChildren())
        {
            statement.prettyPrint();
        }
    }
}

Program ParserManager::getProgram()
{
    return this->currentProgram;
}

void ParserManager::selectAppropriateContent()
{
    short op;

    switch (this->scope)
    {
    case PROGRAM:
        op = 0;
        break;
    case FUNCTION:
        op = 1;
        break;
    case STATEMENT:
        op = 2;
        break;
    case EXPRESSION:
        op = 3;
        break;
    }

    this->currentContent = &this->content[op];
}