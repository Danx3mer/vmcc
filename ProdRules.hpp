#include "tokenTypes.hpp"
#include <vector>
class Expression {
    public:
    bool checkIfValid() {
        for(Token token: tokens) {
            if(token.type!=DIGIT) return false;
        }
        return true;
    }

    Expression() {}
    Expression(std::vector<Token> tokens) :tokens(tokens) {}

    void updateTokens(std::vector<Token> tokens) { this->tokens = tokens; }

    private:
    std::vector<Token> tokens;
};

class Statement {
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

    Statement() {}
    
    void updateTokens(std::vector<Token> tokens) { this->tokens = tokens; }
    
    Expression getChild() { return expression; }

    private:
    Expression expression;
    std::vector<Token> tokens;
};

class Function {
    public:
    bool checkIfValid() {
        for(Statement statement: statements) if(!statement.checkIfValid()) return false;

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

    Function() {}

    void addChild(Statement statement) {
        this->statements.push_back(statement);
    }

    void updateTokens(std::vector<Token> tokens) { this->tokens = tokens; }
    
    std::vector<Statement> getChildren() { return statements; }

    std::string getFuncID() { return this->id; }

    private:
    std::string id;
    std::vector<Token> tokens;
    std::vector<Statement> statements;
};

class Program {
    public:
    bool checkIfValid() {
        for(Function foo: functions) if(!foo.checkIfValid()) return false;
        return functions.size()>0;
    }
    
    void addChild(Function function) {
        this->functions.push_back(function);
    }

    std::vector<Function> getChildren() { return functions; }

    Program() {}
    
    void updateTokens(std::vector<Token> tokens) { this->tokens = tokens; }
    
    private:
    std::vector<Function> functions;
    std::vector<Token> tokens;
};