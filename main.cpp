#include "parser.hpp"
#include "lex.hpp"
#include "codeGen.hpp"

int main(int argc, char* argv[])
{
    std::string assembly = generate(parse(lex(argv[1])));
    
    freopen("assembly.s", "w", stdout);
    std::cout << assembly;

    return 0;
}