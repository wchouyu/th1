#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "Number.h"
using std::string;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }

  bool match( Atom atom );

  bool match(Number number);
  bool match(Variable variable);
  
private:
  string _value;
  bool _assignable = true;
};

#endif
