#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
using std::vector;

class List : public Term {
public:
	string symbol() const
	{
		if (_elements.size()==0)	return "[]";
		else
		{
			string ret="[";
			for (int i=0;i<_elements.size()-1;i++)
				ret+=_elements[i]->symbol()+", ";
			ret+=_elements[_elements.size()-1]->symbol()+"]";
			return ret;
		}
	}
	string value() const
	{
		
		if (_elements.size()==0)	return "[]";
		else
		{
			
			string ret="[";
			for (int i=0;i<_elements.size()-1;i++)
				ret+=_elements[i]->value()+", ";
			ret+=_elements[_elements.size()-1]->value()+"]";
			return ret;
		}
	}
	bool match(Term & term){
		//std::cout << "match_ver1\n";
	}
	int class_number(){return 5;}
public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const
  {
	 if (_elements.size()==0){
		  throw 0;
		  //Term* reture_null=NULL;
		  //return reture_null;
		
	  }
	  if (_elements.size()>=1)
		  return _elements[0];
  }
  List  *tail() const
  {
	  if(_elements.size()>=1)
	  {
		  vector<Term*>v{};
		  for (int i=1;i<_elements.size();i++)
			  v.push_back(_elements[i]);
		  List return_list_buf(v);
		  
		  List *return_list=new List(return_list_buf);
		  
		  return return_list;
	  }
  }
  bool match(List l)
  {
	  //std::cout << "match_ver2\n";
	   
	  if (symbol()==l.symbol())
	  {
		  return true;
	  }
	  else
	  {
		  bool ret_value=false;
		 
			for (int i=0;i<_elements.size();i++)
			{
				if (_elements[i]->symbol()!=l._elements[i]->symbol())//one different(not var) in list return false
					if (_elements[i]->class_number()!=2&&l._elements[i]->class_number()!=2)
						return false;
				if (_elements[i]->class_number()==2&&l._elements[i]->class_number()==2)
					if (_elements[i]->assign()==true&&l._elements[i]->assign()==true)
						ret_value=true;
				if (_elements[i]->class_number()==2)//var in list match num or atom
					if (l._elements[i]->class_number()==1||l._elements[i]->class_number()==0){
						Atom list_buf_atom(l._elements[i]->value());
						_elements[i]->match(list_buf_atom);
						ret_value=true;
					}
				if (l._elements[i]->class_number()==2)//num or atom in list match var
					if (_elements[i]->class_number()==1||_elements[i]->class_number()==0)
					{
						Atom list_buf_atom(_elements[i]->value());
						ret_value=l._elements[i]->match(list_buf_atom);
						
					}
			}
			return ret_value;
	  }
  }
private:
  vector<Term *> _elements;

};

#endif
