#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"


using std::string;



//int count=0;

//class Number;
//class Atom;

int a=0;
Term *again[5]={NULL};
class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){std::cout << "var_1,";}
  
  string value()const{ return _value;}
  string symbol()const{return _symbol;}
  
  int class_number(){return 2;}
  
  bool assign(){return _assignable;};
  //template <class T>
  
  bool match( Term  &input)
  {
	std::cout << "1,";
	bool ret = _assignable;
	std::cout << "2,";
    if(_assignable)
	{
		_value=input.value();
		_assignable = false;
		if (_symbol==input.symbol())
			_assignable = true;
		if (input.class_number()==2)
			if (input.assign()){
				_assignable = true;
				again[a]=this;
				again_ver2[a]=&input;
				a++;
			}
    }
	else 
	{
		Number num(atof(_value.c_str()));
		input.match(num);

  		if (_value==input.value())
  			ret=true;
	}
	std::cout << "3,";

	if (a!=0 && _assignable ==false)
	{
		a--;
		
		Number num(atof(_value.c_str()));
		if (again[a]!=NULL)
		{
			std::cout << "forwarding\n";
			again[a]->match(num);
		}
		if (again_ver2[a]!=NULL)
		{
			std::cout << "forwarding_ver2\n";
			again_ver2[a]->match(num);
		}
	}

	std::cout << "4\n";
	
	/*if (a==0)
		again[a]=NULL;*/

    return ret;
  }
  
  
	
	
	
private:
	string const _symbol;
	string _value;
	bool _assignable = true;
	Term *again_ver2[5]={NULL};
	
};



#endif
