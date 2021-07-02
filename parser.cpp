#include "parser.h"
#include "strings.h"
using namespace std;


void Parser::parse(){
    this->stack.push_back(Symbol(E, NONTERM));
    this->printLM();
    terminal sym_from_in = nextToken();

    while(!this->stack.empty()){
        
        //if the symbol are the same
        if(this->stack.back().getSymbol() == sym_from_in && this->stack.back().getType() == Type::TERM){
            this->accepted.push_back(this->stack.back());
            stack.pop_back();
            this->printLM();
            sym_from_in = nextToken();
        }
        else if (this->stack.back().getType() == Type::TERM){
            cout<< "syntax error" << endl;
            break;
        }
        else if(this->table[this->stack.back().getSymbol()][sym_from_in] == -1){
            cout<< "syntax error" << endl;
            break;
        }else if(this->table[this->stack.back().getSymbol()][sym_from_in] != -1){
            int rule = this->table[this->stack.back().getSymbol()][sym_from_in];
            vector<Symbol> temp_rule = this->rules[rule];
            this->stack.pop_back();
            for (auto i = temp_rule.begin() ; i != temp_rule.end() ; i++){
                if(i->getSymbol() != terminal::EPSILON){
                    this->stack.push_back(*i);
                }
            }
            this->printLM();

        }
    }


}

terminal Parser::nextToken (){
    if (this->inputFile.eof()){
       return terminal::END;
    }
    char ch;
    string token;
    ch = this->inputFile.get();
    while(ch != ' ' && ch != '\r'&& ch != string::npos && ch != '\n' && ch != '\377'){//  ){
        token += ch;
        ch = this->inputFile.get(); 
        
    }
   
    if(token == "id"){
        return terminal::ID;
    }
    if(token == "("){
        return terminal::LPAREN;
    }
    if(token == ")"){
        return terminal::RPAREN;
    }
    if(token == "+"){
        return terminal::PLUS;
    }
    if(token == "*"){
        return terminal::ASTERISK;
    }
    if(token == "e"){
        return terminal::EPSILON;
    }
    else{
        return terminal::END;
    }
}

void Parser::printLM(){

    for (auto i = this->accepted.begin() ; i != this->accepted.end(); i++){
        i->printSymbol();
        cout<<" ";
    }
    cout << "| ";
    for (auto j = this->stack.rbegin() ; j!= this->stack.rend() ; j++){
        j->printSymbol();
        cout <<" ";
    }
    cout<<endl;

}