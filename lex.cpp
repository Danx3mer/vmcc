#include "lex.hpp"
#include <vector>
#include <algorithm>

std::vector<Token> findtStrings(std::vector<char> tkns) {
    std::vector<Token> vec;
    for(int i=0; i<tkns.size(); i++) {
        for(std::string tStr: tokenStrings) {
            bool isTStr=true;
            for(short j=0; j<tStr.size(); j++) {
                if(tStr[j]!=tkns[i+j]) {
                    isTStr=false;
                    break;
                }
                else if(j==(tStr.size()-1)) {
                    i+=j;
                    vec.push_back(Token(KEYWORD,tStr));
                }
            }
            if(!isTStr && tStr==tokenStrings[TKSSIZE-1]) {
                std::string temp=" ";
                temp[0]=tkns[i];
                vec.push_back(Token(Token::getTokenType(tkns[i]), temp));
            } else if(isTStr) break;
        }
    }
    return vec;
}

std::vector<char> getBaseTokens() {
    std::vector<char> tokens = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', // constants - digits
        '{', '}', '(', ')', ';', '*', '.', '=', '/'
    };

    for(short i=0; i<26; i++) {
        tokens.push_back('a'+i);
        tokens.push_back('A'+i);
    }

    return tokens;
}

std::vector<Token> lex() {
    std::ios_base::sync_with_stdio(false);
    
    const std::vector<char> tokens = getBaseTokens();

    std::string inFile;
    std::cout << "Please input the name of the file to be turned into tokens" << "\n";
    std::cin >> inFile;

    freopen(inFile.c_str(), "r", stdin);

    std::vector<char> baseTokens;
    std::string next;

    while(std::getline(std::cin, next)) {
        for(char ch: next) if(std::find(tokens.begin(), tokens.end(), ch)!=tokens.end()) baseTokens.push_back(ch);        
    }

    return findtStrings(baseTokens);
}
