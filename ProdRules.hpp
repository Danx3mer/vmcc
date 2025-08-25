#include "tokenTypes.hpp"
#include <iostream>
#include <vector>

class ProdRule {
    public:
    virtual bool checkIfValid() = 0;
    virtual void addChild(ProdRule child) = 0;

    protected:
    ProdRule(std::vector<Token> tokens) :tokens(tokens) {}
    std::vector<Token> tokens;
};

class Expression: ProdRule {
    public:
    bool checkIfValid() {
        for(Token token: tokens) {
            if(token.type!=DIGIT) return false;
        }
        return true;
    }

    void addChild(Expression _) {}

    Expression(std::vector<Token> tokens) :ProdRule(tokens) {}
};

class Statement: ProdRule {
    public:
    bool checkIfValid() {
        if(tokens[0].content!="return") return false;
        for(Token token: tokens) {
            if(token.content==";") return true;
            if(token.type!=DIGIT) return false;
        }
        
        return true;
    }

    void addChild(Expression child) {
        this->expression = child;
    } 

    Statement(std::vector<Token> tokens) :ProdRule(tokens), expression(tokens) {}

    private:
    Expression expression;
};

class Function: ProdRule {
    public:
    bool checkIfValid() {
        if(!statement.checkIfValid()) return false;

        if(tokens[0].content!="int") return false;

        short i;
        std::string id;
        for(i=1; i<tokens.size(); i++) {
            if(tokens[i].content=="(") break;
            else if(tokens[i].type==SYMBOL) return false;
            else id+=tokens[i].content;
        }

        if(tokens[i+1].content!=")" && tokens[i+2].content != "{" && tokens[tokens.size()-1].content != "}") return false;

        this->id = id;

        return true;
    }

    Function(std::vector<Token> tokens) :ProdRule(tokens), statement(tokens) {}

    void addChild(Statement statement) {
        this->statement = statement;
    }

    std::string getFuncID() { return this->id; }

    private:
    std::string id;
    Statement statement;
};

class Program: ProdRule {
    public:
    bool checkIfValid() {
        return functions.size()>0;
    }
    
    void addChild(Function function) {
        this->functions.push_back(function);
    }

    Program(std::vector<Token> tokens) :ProdRule(tokens) {}
    
    private:
    std::vector<Function> functions;
};