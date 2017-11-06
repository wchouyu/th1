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
	  std::cout << "current char: " << _scanner.currentChar() << "\n";
	  //char cur = _scanner.currentChar();
    int token = _scanner.nextToken();
	
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
		//std::cout << "atom: "<< atom->symbol() << "\n";

		if (atom->symbol()=="[")
		{
			
			if (_scanner.currentChar()!=']' && _scanner.currentChar()!=' ' && _scanner.currentChar()!='\t'){
				vector<Term*> terms = getArgs();
				if(_currentToken == ']'){
					return new List(terms);}
			}
			else 
			{
				if (_scanner.currentChar() == ']')	{
					_currentToken=_scanner.nextToken();
					return new List();
				}

				_scanner.skipLeadingWhiteSpace();
				
				
				vector<Term*> terms= getArgs();
				//List l(terms);std::cout << l.symbol() << "\n";
				
				return new List(terms);
			}

		}

        if(_scanner.currentChar() == '(' ) {
          _scanner.nextToken() ;
          vector<Term*> terms = getArgs();
		  if (terms.size()==0){return new Struct(*atom, terms);}//>
          if(_currentToken == ')')
			  return new Struct(*atom, terms); 
        }
        else
          return atom;
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
