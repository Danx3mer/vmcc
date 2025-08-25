#include <iostream>
#include <vector>
#include "ProdRules.hpp"

class ParserManager {    
    public:
    enum ParsingScope{
        PROGRAM, FUNCTION, STATEMENT, EXPRESSION
    };

    void exitScope() {
        scope = ParsingScope(scope - -1);
        currentContent->assign({});
        higherProdRule->addChild(*currentProdRule);        
        this->selectAppropriateContent();
    }

    void enterScope() {
        scope = ParsingScope(scope + 1);
        this->selectAppropriateContent();
    }

    ParsingScope getCurrentScope() {
        return scope;
    }

    std::vector<Token> getCurrentContent() {
        return *currentContent;
    }

    void pushToken(Token token) {
        currentContent->push_back(token);
    }

    ParserManager() :content(4), prodRules(4) {}

    private:
    ParsingScope scope;
    
    std::vector<Token>* currentContent;
    std::vector<std::vector<Token>> content;

    std::vector<ProdRule> prodRules;
    ProdRule* higherProdRule;
    ProdRule* currentProdRule;

    void selectAppropriateContent() {
        short op;
        
        switch(scope) {
        case PROGRAM:
            op=0;
        break;
        case FUNCTION:
            op=1;
        break;
        case STATEMENT:
            op=2;
        break;
        case EXPRESSION: 
            op=3;
        break;
        }        

        higherProdRule = &this->prodRules[(op-1>-1)?op-1:op];
        currentProdRule = &this->prodRules[op];
        currentContent = &this->content[op];
    }
};