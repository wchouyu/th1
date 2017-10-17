#ifndef NUMBER_H
#define NUMBER_H

#include <string>
//#include "atom.h"
#include <sstream>
using namespace std;

//class Atom;
//class Variable;

class Number : public Term{
public:
	Number (double value):_symbol(std::to_string(value)){
		std::stringstream ss;
		ss << value;
		//_symbol=ss.str();
		_value=ss.str();
	}
	

	string value()const {return _value;}
	string symbol() const {return _symbol;}
	int class_number(){return 1;}
	

	//template <class T>
	bool match(Term &input)
	{
		if (input.class_number()==0)
			return false;
		else if (input.class_number()==1)
			return input.value()==_value;
		else
			return input.match(*this);
	}
	
	
private:
	
	string const _symbol;
	string _value;

	
};
#endif