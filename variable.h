#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
//#include "number.h"
using std::string;

//class Number;
//class Atom;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  
  string value()const{return _value;}
  string symbol()const {return _symbol;}
  
  int class_number(){return 2;}

  //template <class T>
  bool match( Term  &input)
  {
	bool ret = _assignable;
    if(_assignable){
      _value=input.value();
	  //std::cout<<input.value() <<"\n";
      _assignable = false;
		
    }
	else {
		if (_value==input.value())
			ret=true;
		/*if (input.class_number()==2)
			ret=input.match(*this);*/
	}
    return ret;
  }
  //bool match(Number number);
  //bool match(Variable variable);
  
private:
	string const _symbol;
	string _value;
	bool _assignable = true;

};

#endif
