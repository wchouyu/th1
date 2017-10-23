#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;



class Term{

public:
  virtual string symbol() const= 0;

  //virtual string value() const{return symbol();};
  virtual string value() const=0;

  virtual bool match(Term & term) 
  {
	return symbol() == term.symbol();
  }
  virtual int class_number(){return -1;};
  bool assign(){};
  //Term *forward;
  
  
};

class Atom : public Term{
public:
	Atom (string s):_symbol(s),_value(s) {}
	string symbol() const{return _symbol;}
	string value()const{return _value;}
	int class_number(){return 0;}

	//template <class T>
	bool match(Term &input)
	{
		if (input.class_number()==0)
			return input.value() == _symbol;
		else if (input.class_number()==1)
			return false;
		else if (input.class_number()==5)
			return false;
		else 
			return input.match(*this);
	}

  
private:
	string const _symbol;
	string _value;
};

#endif
