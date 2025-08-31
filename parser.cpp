#include "lex.hpp"
#include "parser.hpp"
#include "ParserManager.hpp"

Program parse(std::vector<Token> tokens)
{
    Program prog;

    ParserManager pMnger(tokens);

    for (Token token : tokens)
    {
        pMnger.pushToken(token);

        if (token.type == KEYWORD)
            pMnger.enterScope();

        switch (pMnger.getCurrentScope())
        {
        case ParserManager::ParsingScope::FUNCTION:
        {
            if (token.content == "{")
                pMnger.enterScope();
            else if (token.content == "}")
                pMnger.exitScope();
        }
        break;

        case ParserManager::ParsingScope::STATEMENT:
        {
            if (token.type == SEMICOLON)
                pMnger.exitScope();
        }
        break;

        case ParserManager::ParsingScope::EXPRESSION:
        {
            if(token.type == KEYWORD && !pMnger.getCurrentContent().empty()) {
                pMnger.exitScope();
            }
            else if(token.type == SEMICOLON) {
                pMnger.popLastToken();
                pMnger.exitScope();
                pMnger.pushToken(token);
                pMnger.exitScope();
            }
            else if (token.type != DIGIT && !(token.type==KEYWORD && pMnger.getCurrentContent().empty())) {
                pMnger.exitScope();
            }
        }
        break;
        }
    }

    std::cout << pMnger.getCurrentScope();

    pMnger.prettyPrint();

    return pMnger.getProgram();
}