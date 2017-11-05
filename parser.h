#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){
	  _scanner.checkInput();
	  
  }
  Term* createTerm(){
    int token = _scanner.nextToken();
	
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
		//std::cout << "atom: "<< atom->symbol() << "\n";
        if(_scanner.currentChar() == '(' ) {
          _scanner.nextToken() ;
		  
          vector<Term*> terms = getArgs();
		  
          if(_currentToken == ')'){
			  return new Struct(*atom, terms);}
		 
		 
        }
        else
          return atom;
    }
	else if (token== ATOMSC)
	{
		//case1 has term in list
		//std::cout << "current " << _scanner.currentChar() << "\n";
		if (_scanner.currentChar()!=']' && _scanner.currentChar()!=' ' && _scanner.currentChar()!='\t'){
			vector<Term*> terms = getArgs();
			if(_currentToken == ']')
				return new List(terms);
		}
		else
		{
			_scanner.skipLeadingWhiteSpace();
			vector<Term*> terms= getArgs();
			
			return new List(terms);
		}
		
	}
	
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif
