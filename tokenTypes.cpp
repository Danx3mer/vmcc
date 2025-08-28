#include "tokenTypes.hpp"

TokenType Token::getTokenType(char unLexedToken)
{
    for (short i = 0; i < 26; i++)
        if (unLexedToken == ('a' + i) || unLexedToken == ('A' + i))
            return TokenType::CHARACTER;

    for (short i = 0; i < 10; i++)
        if (unLexedToken == ('0' + i))
            return TokenType::DIGIT;

    switch (unLexedToken)
    {
    case '{':
        return TokenType::SYMBOL;
        break;
    case '}':
        return TokenType::SYMBOL;
        break;
    case '(':
        return TokenType::SYMBOL;
        break;
    case ')':
        return TokenType::SYMBOL;
        break;
    case ';':
        return TokenType::SEMICOLON;
        break;
    case '*':
        return TokenType::SYMBOL;
        break;
    case '.':
        return TokenType::SYMBOL;
        break;
    case '=':
        return TokenType::SYMBOL;
        break;
    case '/':
        return TokenType::SYMBOL;
        break;
    default:
        return TokenType::UNDEFINED;
    }
}