#include "symbolTable.hpp"

#include <vector>
#include <iterator>

//Returns true if an identifier name is used one or fewer times in the entire global stack
bool symbolTable::verify(std::string tokenName) {
    std::vector<std::string>::iterator it;
    int numInstances = 0;

    for(it = symbolTable::stack.begin(); it < symbolTable::stack.end(); it++) {
        if(*it == tokenName) {
            numInstances++;
        }
    }

    if(numInstances <= 1)
        return true;

    return false;
}

//Pushes a token onto TOS
void symbolTable::Scope::push(std::string identifier) {
    symbolTable::stack.push_back(identifier);
    varCount++;
}

//Removes a token from TOS
void symbolTable::Scope::pop() {
    symbolTable::stack.pop_back();
    varCount--;
}

//Returns distance from TOS if found, returns -1 otherwise
int symbolTable::Scope::find(std::string tokenInstance) {
    std::vector<std::string>::iterator it;
    int stackCounter = 0;

    for(it = symbolTable::stack.end(); it > symbolTable::stack.begin(); it--) {
        if(*it == tokenInstance) {
            return stackCounter;
        }
        stackCounter++;
    }

    return -1;
}