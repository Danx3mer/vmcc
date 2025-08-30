#include "prodRules.hpp"

class ParserManager {    
    public:
    enum ParsingScope{
        PROGRAM, FUNCTION, STATEMENT, EXPRESSION
    };

    void exitScope() {
        switch(this->scope) {
            case FUNCTION: 
            {
                this->currentFunction.updateTokens(*this->currentContent);
                this->currentProgram.addChild(this->currentFunction);
                std::cout << "EXIT FUNC";
            }
            break;
            case STATEMENT: 
            {
                this->currentStatement.updateTokens(*this->currentContent);
                this->currentFunction.addChild(this->currentStatement);
                std::cout << "EXIT st";
            }
            break;
            case EXPRESSION: 
            {
            this->currentStatement.addChild(Expression(*this->currentContent));
            std::cout << "EXIT exp";
            }
            break;
        }

        this->scope = ParsingScope(this->scope -1);
        this->currentContent->assign({});
        this->selectAppropriateContent();
    }

    void enterScope() {
        this->scope = ParsingScope(this->scope + 1);
        this->selectAppropriateContent();
        if(lastToken.type==KEYWORD) this->currentContent->push_back(lastToken);
    }

    ParsingScope getCurrentScope() {
        return this->scope;
    }

    std::vector<Token> getCurrentContent() {
        return *this->currentContent;
    }

    void pushToken(Token token) {
        this->lastToken = token;
        this->selectAppropriateContent();
    }

    ParserManager() :content(4), scope(PROGRAM), lastToken(Token()) {}

    void printParsedProgram() {
        for(Function foo: this->currentProgram.getChildren()) {
           std::cout << foo.getFuncID() << "\n";
            for(Statement statement: foo.getChildren())
                std::cout << "Statement" << "\n";
        }

        //std::cout << currentFunction.getFuncID();
        //std::cout << currentStatement.checkIfValid();
        //std::cout << currentExpression.checkIfValid();
    }

    private:
    ParsingScope scope;
    
    std::vector<Token>* currentContent;
    std::vector<std::vector<Token>> content;

    Program currentProgram;
    Function currentFunction;
    Statement currentStatement;
    Expression currentExpression;

    Token lastToken;

    void selectAppropriateContent() {
        short op;
        
        switch(this->scope) {
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

        this->currentContent = &this->content[op];
    }
};