#include "codeGen.hpp"

std::string generate(Program program) {
    std::string assembly = "";
    for(Function function: program.getChildren()) {
        assembly += "\t.globl " + function.getFuncID();
        assembly += "\n" + function.getFuncID() + ":";

        for(Statement statement: function.getChildren()) {
            statement.checkIfValid();
            switch(statement.getType()) {
                case Statement::StatementType::RETURN: 
                {
                    assembly += "\n\tmovl\t$" + statement.getChild().getValue() + ", %eax\n\tret\n";
                }
                break;
            }
        }
    }
    return assembly;
}