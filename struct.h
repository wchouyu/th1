#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>

using std::string;

class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }
  string symbol() const {
	  
    string ret = _name.symbol() + "(";
	if (_args.size()==0){
		ret=_name.symbol()+"()";
		return ret;
	}
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }
  string value() const {
    string ret = _name.symbol() + "(";
	if (_args.size()==0)
	{
		ret=_name.symbol()+"()";
		return ret;
	}
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  bool match(Term &term)
  {
	  Struct * ps = dynamic_cast<Struct *>(&term);
	  if (typeid(term)!=typeid(Struct))
		  return false;
	  if (typeid(term)==typeid(Struct))
	  {
		  if (ps){
			  if (!_name.match(ps->_name))
				  return false;
			  if(_args.size()!= ps->_args.size())
				  return false;

			  for(int i=0;i<_args.size();i++)
			  {
				  if (! ( ps->_args[i]->match(*_args[i]) ) )
						  return false;
			  }
			 
		  }
      return true;
	  }
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
