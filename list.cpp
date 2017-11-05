#include "list.h"
#include "variable.h"
#include <typeinfo>

bool List::match(List &l) 
{
	
		if(value()==l.value())	return true;
		else
		{
			bool ret_value=false;
			for (int i=0;i<_args.size();i++)
			{
				Variable *var1=dynamic_cast<Variable*>(_args[i]);
				Atom *at1=dynamic_cast<Atom*>(l._args[i]);
				Number *num1=dynamic_cast<Number*>(l._args[i]);
				if (var1)
				{	
					if(num1||at1)
						ret_value=_args[i]->match(*l._args[i]);	
				}

				Variable *var2=dynamic_cast<Variable*>(l._args[i]);
				Atom *at2=dynamic_cast<Atom*>(_args[i]);
				Number *num2=dynamic_cast<Number*>(_args[i]);
				if (var2){
					if(num2||at2)
						ret_value=l._args[i]->match(*_args[i]);
				}

				//=============================================

				if (var1 && var2)
				{
					ret_value=_args[i]->match(*l._args[i]);
				}

			}
			return ret_value;
		}
}
