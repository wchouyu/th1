#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"


using std::string;



//int count=0;

//class Number;
//class Atom;

int a=0;int a_ver2=0;
Term *again[5]={NULL};
Term *again_ver2[5]={NULL};
int b=3;

int again_delete_count=0;
string again_delete[50]={};

Term *str_var[5]={NULL};
Term *list_var[5]={NULL};
class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){
	  for (int i=0;i<again_delete_count;i++)
	  {
		  if (again_delete[i]==s)
		  {
			  a=0;b=3;a_ver2=0;again_delete_count=0;
			  break;
		  }
	  }
	  again_delete[again_delete_count]=s;
	  again_delete_count++;
  }
  
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
		
		if (_symbol==input.symbol()){
			_assignable = true;
			return true;//1019_0318
		}
		else if (input.class_number()==2)
		{
			
			if (input.assign()){
				_assignable = true;
				again[a]=this;
				again_ver2[a_ver2]=&input;
				a++;a_ver2++;
				
			}
			else
			{
				return true;
			}
		}
		else if (input.class_number()==4)	
		{
			
				_assignable = true;//e
				str_var[0]=&input;
				b=4;
				again[a]=this;
				//a++;
		}
		else if (input.class_number()==5)
		{
			
			ret=true;
			string s_for_list=input.symbol();
			if (s_for_list.find(_symbol,0)!=-1){
				_assignable=true;
				_value=_symbol;
				return false;//Don't care
			}
			else if (s_for_list.find(_symbol,0)==-1){//no this variable in the list
				ret=true;

				
				////////Y match L(containX),X match atom
				_assignable=true;
				list_var[0]=&input;
				b=5;
				again[a]=this;
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
	


	if (b==5&&_assignable==false)
	{
		
		b=3;
		Atom at2(list_var[0]->value());
		if (list_var!=NULL)
			if (again[a]!=NULL)
				again[a]->match(at2);
		return ret;
	}
	if (b==4 &&_assignable==false)
	{
			b=3;
			Atom at2(str_var[0]->value());
			
			if (str_var!=NULL)
				if (again[a]!=NULL)
					again[a]->match(at2);
			//std::cout <<str_var[0]->value() <<"\n";
			//std::cout <<at2.value() <<"\n";
			return ret;
	}
	
	if (a!=0 && _assignable ==false)
	{
		a--;
		Atom at(_value);
		//std::cout << "before if again_ver2 again input: " << num.value() <<"\n";
		if (again[a]!=NULL)
		{
			//std::cout << "forwarding\n";
			again[a]->match(at);
			//std::cout << "in forwarding	a:" << a << "again[a]:" << again[a] <<"\n";  
			//again[a]=NULL;
			
		}
		a_ver2--;
		if (again_ver2[a_ver2]!=NULL)
		{
			//std::cout << "forwarding_ver2\n";
			//std::cout << "before again_ver2 again input: " << num.value() <<"\n";
			again_ver2[a_ver2]->match(at);
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
	
	
};



#endif
