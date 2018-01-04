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
		  string left=_left->result();
		  left.pop_back();
		  string right=_right->result();
		  right.pop_back();
		  ret= left+", "+right+".";
		  if (left==right || right=="true")
			  ret=left+".";
		  else if (left=="true")	ret=right+".";
		  if (left=="false" || right == "false")
			  ret="false";
		  if (left.find(right)!=string::npos)
			  ret=left+".";
	  }
	  else
		   ret+="false.";
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
	  string ret = "";
	  if (evaluate()){
		  string left=_left->result();
		  left.pop_back();
		  string right=_right->result();
		  right.pop_back();
		  ret= left+"; "+right+".";
		  if (right=="false")	ret=left+".";
		  else if (left=="false")	ret=right+".";
	  }else	ret="false";

	  return ret;
  }
private:
  Exp * _left;
  Exp * _right;
};
#endif
