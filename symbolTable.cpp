#include "symbolTable.hpp"

#include <vector>
#include <iterator>

//Returns true if an identifier name is used one time in the entire global stack
bool symbolTable::verify(token::Token token) {
    std::vector<token::Token>::iterator it;
    int numInstances = 0;

    for(it = symbolTable::stack.begin(); it < symbolTable::stack.end(); it++) {
        if(it->tokenInstance == token.tokenInstance) {
            numInstances++;
        }
    }

    if(numInstances == 1)
        return true;

    return false;
}

//Pushes a token onto TOS
void symbolTable::Scope::push(token::Token token) {
    symbolTable::stack.push_back(token);
    varCount++;
}

//Removes a token from TOS
void symbolTable::Scope::pop() {
    symbolTable::stack.pop_back();
    varCount--;
}

//Returns distance from TOS if string identifier is found, returns -1 otherwise
int symbolTable::Scope::find(token::Token tokenInstance) {
    std::vector<token::Token>::iterator it;
    int stackCounter = 0;

    for(it = symbolTable::stack.end(); it > symbolTable::stack.begin(); it--) {
        if(it->tokenInstance == tokenInstance.tokenInstance) {
            return stackCounter;
        }
        stackCounter++;
    }

    return -1;
}