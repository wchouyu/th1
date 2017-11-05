#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>

using std::string;
using std::vector;



class List: public Term {
public:


  Term * args(int index) {
    return _args[index];
  }

  
  string symbol() const
	{
		if (_args.size()==0)	return "[]";
		else
		{
			string ret="[";
			for (int i=0;i<_args.size()-1;i++)
				ret+=_args[i]->symbol()+", ";
			ret+=_args[_args.size()-1]->symbol()+"]";
			return ret;
		}
	}
  string value() const
	{
		
		if (_args.size()==0)	return "[]";
		else
		{
			
			string ret="[";
			for (int i=0;i<_args.size()-1;i++)
				ret+=_args[i]->value()+", ";
			ret+=_args[_args.size()-1]->value()+"]";
			return ret;
		}
	}

  
public:
	List (): _args() {}
	List (vector<Term *>const &elements):_args(elements){}
	Term *head()const
	{
		if (_args.size() >=1)
			return _args[0];
		else
			throw std::string("Accessing head in an empty list");
	}
	List *tail() const
	{
		if (_args.size()>=1)
		{
			vector<Term*>v{};
			for (int i=1;i<_args.size();i++)
				v.push_back(_args[i]);
			List return_list_buf(v);
			List *return_list=new List(return_list_buf);
			return return_list;
		}
		else
			throw std::string("Accessing tail in an empty list");
	}
	bool match(List &l);
private:
  
  std::vector<Term *> _args;
  
};

#endif
