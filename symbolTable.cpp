#include "symbolTable.hpp"

#include <vector>
#include <iterator>
#include <iostream>

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
    std::cout << "abt to push\n";
    symbolTable::stack.push_back(token);
    std::cout << symbolTable::stack.back().tokenInstance << " has been pushed to the stack.\n";
    varCount++;
}

//Removes a token from TOS
void symbolTable::Scope::pop() {
    std::cout << "Popping " << symbolTable::stack.back().tokenInstance << " from the stack.\n";
    symbolTable::stack.pop_back();
    varCount--;
}

//Returns distance from TOS if string identifier is found, returns -1 otherwise
int symbolTable::Scope::find(token::Token tokenInstance) {
    std::cout << "Do I make it into find()?\n";
    std::vector<token::Token>::iterator it;
    int stackCounter = 0;


    //Maybe prevents segFault
    it = symbolTable::stack.end();
    if(it == symbolTable::stack.begin()) {
        return -1;
    }

    std::string stopsegfault = it->tokenInstance;
    std::cout << "About to enter for loop in find()\n";
    
    for(it = symbolTable::stack.end(); it > symbolTable::stack.begin(); it--) {
        std::cout << "inside of for loop\n";
        if(it->tokenInstance == tokenInstance.tokenInstance) {
            std::cout << "returning stackCounter\n";
            return stackCounter;
        }
        std::cout << "incrementing stackCounter\n";
        stackCounter++;
    }

    std::cout << "returning -1\n";
    return -1;
}