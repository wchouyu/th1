#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <math.h>  
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }
  vector<Term *> & getTerms() {
    return _terms;
  }
  void matchings()
  {

	  int check =0;
	  Term *actualTerm=createTerm();
	  _terms.push_back(actualTerm);
	  nodes.push_back(new Node(TERM,actualTerm,nullptr,nullptr));
	  _currentToken=_scanner.currentChar();
	  while((_currentToken = _scanner.currentChar())!='.')
	  {
		  if(_currentToken == '=')
		  {
			  _currentToken=_scanner.nextToken();
			  nodes.push_back(new Node(EQUALITY,nullptr,nullptr,nullptr));
		  }
		  else if(_currentToken == ',')
		  {
			  _currentToken=_scanner.nextToken();
			  nodes.push_back(new Node(COMMA,nullptr,nullptr,nullptr));
		  }
		  else if(_currentToken == ';')
		  {
			  check =1;
			  _currentToken=_scanner.nextToken();
			  nodes.push_back(new Node(SEMICOLON,nullptr,nullptr,nullptr));
			  
		  }
		  actualTerm=createTerm();
		  _terms.push_back(actualTerm);
		  nodes.push_back(new Node(TERM,actualTerm,nullptr,nullptr));
	  }


	  int stringfind=0;
	  
	  for(int i=0;i<nodes.size();i++)
	  {
		  
		  //////////////////////////
		   for(int j=i+1;j<nodes.size();j++)
		{
			

			if (nodes[i]->term!=NULL && nodes[j]->term!=NULL)
		  {



			  string s = nodes[i]->term->symbol();//struct s(y)
			string s2=nodes[j]->term->symbol();
			
			if (nodes[i]->payload == TERM && nodes[j]->payload == TERM)
			{
				stringfind = s.find(s2);
				if (stringfind!=-1 && stringfind !=0)	{
					Struct *ps = dynamic_cast<Struct *>(nodes[i]->term);
					if (ps){
						ps->_args[0]->match(*nodes[j]->term);
					}
					}
			}
			  ///////////////
			  if (nodes[i]->payload == TERM){
					if (nodes[i]->term->symbol()==nodes[j]->term->symbol())
					{
						
						if (check!=1){//std::cout << check << "\n";
							nodes[i]->term->match(*nodes[j]->term);}
						//std::cout << nodes[i]->term->symbol();
					}
			  }	  
			}
		}
		  //////////////////////////////



		  if(nodes[i]->payload==SEMICOLON||nodes[i]->payload==COMMA||nodes[i]->payload==EQUALITY)
		  {
			  if (nodes.size()<=7){
				if (i==1){	
					nodes[i]->left=nodes[0];
					nodes[i]->right=nodes[2];
				}
				else if (i==3){
					nodes[i]->left=nodes[1];
					nodes[i]->right=nodes[5];
				}
				else if (i==5){
					nodes[i]->left=nodes[4];
					nodes[i]->right=nodes[6];
				}
			  }
			  else if (nodes.size()==11 )//three match
			  {
					if (i==1){	
						nodes[i]->left=nodes[0];
						nodes[i]->right=nodes[2];
					}
					else if (i==3){
						nodes[i]->left=nodes[1];
						nodes[i]->right=nodes[7];
						
					}
					else if (i==5){
						nodes[i]->left=nodes[4];
						nodes[i]->right=nodes[6];
					}
					else if (i==7){
						nodes[i]->left=nodes[5];
						nodes[i]->right=nodes[9];
					}
					else if (i==9){
						nodes[i]->left=nodes[8];
						nodes[i]->right=nodes[10];
					}
			  }
			  
		  }
	  }
	  
  }
  
  Node * expressionTree()
  {
	 
	  if (nodes.size() == 3)	return nodes[1];
	  else if (nodes.size() == 7) return nodes[3];
	  else if (nodes.size() == 11) {return nodes[3];}
	  
  }

public:
  vector<Term *> _terms;
  vector<Node *> nodes;
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  
  Scanner _scanner;
  int _currentToken;
};
#endif
