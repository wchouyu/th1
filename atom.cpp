#include "include/atom.h"
#include "include/variable.h"
#include "include/number.h"

bool Atom::match(Atom a)
{
	return _symbol==a._symbol;
}
bool Atom::match(Number num)
{
	return false;
}
bool Atom::match(Variable &var)
{
	Atom a(*this);
	return var.match(a);
}
