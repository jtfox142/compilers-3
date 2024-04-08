#include "parser.hpp"
#include "statSem.hpp"
#include "symbolTable.hpp"

//Prototypes
void processBlock(node::Node*);
void processVars(node::Node*, symbolTable::Scope*);
void processStats(node::Node*, symbolTable::Scope*);

namespace {

    //Global for the purpose of ensuring that local identifiers don't have the same name as globals
    symbolTable::Scope *_globalSTV = new symbolTable::Scope();

}

void statSem::driver() {
    //Get the parse tree from parser
    node::Node* tree = parser::parse();

    //<program> -> <vars> tape <func> <block> | <vars> tape <block>
    processVars(tree->getChildOne(), _globalSTV);

    traversePreorder(tree);

    //Traverse the parse tree.
}

//root, left, middle, right
void traversePreorder(node::Node *root) {
    if(root == NULL) return;

    if(root->getData().tokenInstance == "block()")
        processBlock(root);

    traversePreorder(root->getChildOne());
    traversePreorder(root->getChildTwo());
    traversePreorder(root->getChildThree());
    traversePreorder(root->getChildFour());
    traversePreorder(root->getChildFive());
    traversePreorder(root->getChildSix());
    traversePreorder(root->getChildSeven());
    traversePreorder(root->getChildEight());
}

//Starts a local scope for new identifiers within the block
void processBlock(node::Node *root) {
    symbolTable::Scope *local = new symbolTable::Scope();

    //<block> -> { <vars> <stats> }
    processVars(root->getChildTwo(), local);
    processStats(root->getChildThree(), local);

    //Pop the local vars off the stack before leaving the block
    for(int count = 0; count < local->getVarCount(); count++) {
        local->pop();
    }
}


void processVars(node::Node *root, symbolTable::Scope *local) {
    //<vars> -> empty | create Identifier ; | create Identifier := Integer ; <vars>
    if(root == NULL) return;

    //If vars() subtree is not empty, push the identifier onto the stack
    if(root->getChildOne()->getData().tokenInstance == "create") {
        token::Token token = root->getChildTwo()->getData();

        //Ensure the identifier hasn't been used before
        if(local->find(token) == -1 && _globalSTV->find(token) == -1) {
            local->push(token);
        }
        else {
            std::cerr << "Static Semantic Error: Identifier " << token.tokenInstance << " is declared multiple times.";
            exit(1);
        }
    }

    //If vars() is called again in the subtree, load that onto the stack as well
    if(root->getChildSix() != NULL) {
        processVars(root->getChildSix(), local);
    }
}

void processStats(node::Node *root, symbolTable::Scope *local) {
    //<stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; |
    //<goto> ; | <label> ; | <pick> ;  

    if(root->getChildOne()->getData().tokenInstance == "block()")
        processBlock(root->getChildOne());
    
    //If I push tokens onto the stack instead of strings, then I can simply traverse the tree until an idTok is found
    //The alternative is a long series of if statements and complicated BS

}