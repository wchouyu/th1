#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Variable;
class Number;
class Atom {
public:
  Atom (string s):_symbol(s) {}
  Atom (const Atom &a):_symbol(a._symbol){}
  //bool operator ==(Atom a) {return _symbol == a._symbol;}

  bool match(Atom a);
  bool match(Variable &var);
  bool match(Number num);

  string _symbol;
private:
	//Number num;
};

#endif
