#include "prodRules.hpp"

class ParserManager {    
    public:
    enum ParsingScope{
        PROGRAM, FUNCTION, STATEMENT, EXPRESSION
    };

    void exitScope() {
        switch(scope) {
            case FUNCTION: 
            currentProgram.addChild(currentFunction);
            break;
            case STATEMENT:
            currentFunction.addChild(currentStatement);
            break;
            case EXPRESSION:
            currentStatement.addChild(Expression(*currentContent));
            break;
        }

        scope = ParsingScope(scope - -1);
        currentContent->assign({});
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

    ParserManager() :content(4) {}

    void printParsedProgram() {
        for(Function foo: currentProgram.getChildren()) {
            std::cout << foo.getFuncID() << "\n";
            for(Statement statement: foo.getChildren())
                std::cout << "Statement" << "\n";
        }
    }

    private:
    ParsingScope scope;
    
    std::vector<Token>* currentContent;
    std::vector<std::vector<Token>> content;

    Program currentProgram;
    Function currentFunction;
    Statement currentStatement;
    Expression currentExpression;

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

        currentContent = &this->content[op];
    }
};