#include "symbol.h"
#include "strings.h"
using namespace std;


Type Symbol::getType(){
    return this->type;
}

int Symbol::getSymbol(){
    return this->symbol;
}

void Symbol::printSymbol(){
    if(this->type == Type::NONTERM){  
        cout<< tokenStrings[this->symbol] ;
    }
    else if(this->type == Type::TERM){
        cout<< terminalStrings[this->symbol] ;
    }

}