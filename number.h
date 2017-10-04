#ifndef NUMBER_H
#define NUMBER_H

#include <string>
//#include "atom.h"
#include <sstream>
using namespace std;

//class Atom;
//class Variable;

class Number{
public:
	//Number (){}
	Number (int s){
		std::stringstream ss;
		ss << s;
		_symbol=ss.str();
		_value=ss.str();
	}
	//Number (const Number &num):_value(num._value),_symbol(num._symbol){}

	string value(){ return _value; }
	string symbol(){return _symbol;}
	int class_number(){return 1;}
	

	template <class T>
	bool match(T &input)
	{
		if (input.class_number()==0)
			return false;
		else if (input.class_number()==1)
			return input.value()==_value;
		else
			return input.match(*this);
	}
	//bool match(Variable &var);
	//bool match(Number num);
	
private:
	
	string _symbol;
	string _value;
	
};
#endif