#ifndef EXP_H
#define EXP_H

#include <string>
#include <typeinfo>

#include "atom.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string result() = 0;
  
};

class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }

  string result()
  {
	  string ret = "";
	  if (evaluate()){
		  ret=ret+_left->symbol()+" = "+_right->value() + ".";
		  if (_left->type()=="Var" && _right->type()=="Var")
			  ret="true.";
	  }
	  else
		  ret+="false.";

	  return ret;
	  
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }
  string result()
  {
	  string ret = "";
	  if (evaluate()){
		  ret= _left->result()+", "+_right->result()+".";
	  }
	  return ret;
  }
private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }
  string result()
  {
	  string ret = "ff2";
	  return ret;
  }
private:
  Exp * _left;
  Exp * _right;
};
#endif
