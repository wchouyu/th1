#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
using std::string;

//class Number;
//class Atom;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  
  string value()const{ return _value;}
  string symbol()const{return _symbol;}
  
  int class_number(){return 2;}
  
  bool assign(){return _assignable;};
  //template <class T>
  bool match( Term  &input)
  {
	bool ret = _assignable;
	//std::cout << _symbol <<"=>assignable:" <<_assignable<<"\n";
    if(_assignable)
	{
		
		_value=input.value();
		_assignable = false;
		if (input.class_number()==2)
			if (input.assign())
				_assignable = true;
    }
	else 
	{
		//ret=input.match(*this);
		
		Number num(atof(_value.c_str()));
		input.match(num);

  		if (_value==input.value())
  			ret=true;
	}
    return ret;
  }

	

private:
	string const _symbol;
	string _value;
	bool _assignable = true;

};

#endif
