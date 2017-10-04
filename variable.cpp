#include "variable.h"
//#include "atom.h"
//#include "Number.h"


bool Variable::match(Atom atom){
	 bool ret = _assignable;

    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
    }
	else {
		if (_value==atom._symbol)
			ret=true;
	}
    return ret;
}

bool Variable::match(Number number){
	 bool ret = _assignable;
	  if (_assignable){
		  _value = number.symbol();
		  _assignable = false;
	  }
	  else {
		  if (_value==number.symbol())
			ret=true;
	}
	  return ret;
}

bool Variable::match(Variable variable){
	 if (_value == variable.value())
		  return true;
	  else
		  return false;
}