#pragma once
#include "tokenTypes.hpp"
#include <iostream>
#include <vector>

#define TKSSIZE 2

const std::string tokenStrings[TKSSIZE] = {
    "int", "return"};

std::vector<Token> findtStrings(std::vector<char>);

std::vector<char> getBaseTokens();

std::vector<Token> lex(std::string inFile);
