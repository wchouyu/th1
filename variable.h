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
Term *again[3]={NULL};
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

	//forwarding

	//std::cout <<".h:" <<input.forward <<"\n";
	
	//std::cout <<"in match\n";

	if (a!=0 && _assignable ==false)
	{
		a--;
		//std::cout << "forwarding\n";
		Number num(atof(_value.c_str()));
		if (again[a]!=NULL)
			again[a]->match(num);
		if (again_ver2[a]!=NULL)
			again_ver2[a]->match(num);
	}
	if (a==0)
		again[a]=NULL;

    return ret;
  }
  
  
	
	
	
private:
	string const _symbol;
	string _value;
	bool _assignable = true;
	Term *again_ver2[3]={NULL};
	
};



#endif
