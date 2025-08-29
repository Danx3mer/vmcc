#include "lex.hpp"
#include "parser.hpp"
#include "ParserManager.hpp"

void parse() {
	std::vector<Token> tokens = lex();

    Program prog;
    
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

    pMnger.printParsedProgram();
}