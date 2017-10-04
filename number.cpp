#include "include/number.h"
#include "include/atom.h"
#include "include/variable.h"

bool Number::match(Number num)
{
	return _value==num.value();
}
bool Number::match(Atom a)
{
	return false;
}
bool Number::match(Variable &var)
{
	Number num(*this);
	return var.match(num);
}