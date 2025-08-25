#include <iostream>
#include "lex.cpp"
#include "ParserManager.hpp"
#include "ProdRules.hpp"

int main() {
	std::vector<Token> tokens = lex();

    Program prog(tokens);
    
    ParserManager pMnger;

    for(Token token: tokens) {
        pMnger.pushToken(token);
        
		if(token.type==KEYWORD) pMnger.enterScope();
        
        switch(pMnger.getCurrentScope()) {
            case ParserManager::ParsingScope::FUNCTION: {
                if(token.content=="{") pMnger.enterScope();   
                else if(token.content=="}") pMnger.exitScope();
            }
            break;
            
			case ParserManager::ParsingScope::STATEMENT: {
				if(token.content==";") pMnger.exitScope();					
			}
			break;

			case ParserManager::ParsingScope::EXPRESSION: {
				if(token.type!=DIGIT) pMnger.exitScope();
			}
            break;
        }
    }
}