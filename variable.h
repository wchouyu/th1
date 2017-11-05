#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include <typeinfo>
#include "atom.h"
#include "list.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _inst(0){}
  string value() const {
    if (_inst)
      return _inst->value();
    else
      return Term::value();
  }
  bool match( Term & term ){
    if (this == &term)
      return true;
    if(!_inst){
      _inst = &term ;
      return true;
    }
	////
	
	////
    return _inst->match(term);
  }
public:

	bool match(List &l)
	{
		
		if (l.symbol().find(symbol(),0) != -1)
		{
			//_inst= &l;//dangerous
			return false;
		}
		else//no this variable in the list
		{
			_inst=&l;
			return true;
		}
		
	}
	
private:
  Term * _inst;
};

#endif
