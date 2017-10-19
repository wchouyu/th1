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
int b=3;
Term *str_var;
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
	//std::cout << "in match a:" << a <<"\n";
	bool ret = _assignable;
	
    if(_assignable)
	{
		_value=input.value();
		_assignable = false;
		//std::cout << "input:" <<input.symbol()<<"\t"<<input.value() << "\n";
		
		
		if (_symbol==input.symbol()){
			_assignable = true;
			return true;//1019_0318
		}

		else if (input.class_number()==2||input.class_number()==4)
		{
			if (input.class_number()==4)	
			{
				_assignable = true;
				str_var=&input;
				b=4;
			}
			if (input.assign()){
				_assignable = true;
				again[a]=this;
				again_ver2[a]=&input;
				a++;
				
			}
			else
			{
				return true;
			}
		}

    }
	else 
	{
		if (input.class_number()==2){
			Number num(atof(_value.c_str()));
			input.match(num);
		}

  		if (_value==input.value()){
  			ret=true;

		}
	}

	/////////
	if (a!=0 && _assignable ==false)
	{
		a--;
		
		/*if (b==4 &&_assignable==false)
		{
			b=3;
			Atom at2(str_var->value());
			if (str_var!=NULL)
				if (again[a]!=NULL)
					again[a]->match(at2);
			std::cout <<str_var->value() <<"\n";
			std::cout <<at2.value() <<"\n";
			return ret;
		}*/
		Atom at(_value);
		//std::cout << "before if again_ver2 again input: " << num.value() <<"\n";
		if (again[a]!=NULL)
		{
			//std::cout << "forwarding\n";
			again[a]->match(at);
			//std::cout << "in forwarding	a:" << a << "again[a]:" << again[a] <<"\n";  
			//again[a]=NULL;
			
		}
		if (again_ver2[a]!=NULL)
		{
			//std::cout << "forwarding_ver2\n";
			//std::cout << "before again_ver2 again input: " << num.value() <<"\n";
			again_ver2[a]->match(at);
			//std::cout << "again_ver2 again input: " << num.value() << "\n";
			//again_ver2[a]=NULL;
		}
	}
////////////
	
	
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
