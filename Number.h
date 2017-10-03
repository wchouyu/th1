#ifndef NUMBER_H
#define NUMBER_H

#include <string>
//#include "atom.h"

using namespace std;

class Atom;
class Variable;

class Number{
public:
	//Number (){}
	Number (string s):_value(s),_symbol(s){}
	Number (const Number &num):_value(num._value),_symbol(num._symbol){}

	string symbol(){return _symbol;}
	string value(){return _value;}

	bool match(Number num);
	bool match(Atom a);
	bool match(Variable &var);
private:
	string _symbol;
	string _value;
	
};
#endif