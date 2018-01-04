#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>

using std::stack;



class Parser{
public:
	
  Parser(Scanner scanner) : _scanner(scanner), _terms() {}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
		Variable *ch_reuse=new Variable(symtable[_scanner.tokenValue()].first);
		std::cout << ch_reuse->symbol() << "\n";
		if (record.size() == 0 ){
			record.push_back(ch_reuse);}
		for (int i=0;i<record.size();i++)
		{
			if (record[i]->symbol()==ch_reuse->symbol())
				return record[i];
			else
				record.push_back(ch_reuse);
		}
		return ch_reuse;
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
      throw string("Unbalanced operator");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      if(args.size()==0){
        return new Atom("[]");
      }
      return new List(args);
    } else {
      throw string("Unbalanced operator");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void buildExpression(){
    // createTerm();
    disjunctionMatch();
    restDisjunctionMatch();

    if (createTerm() != nullptr  )
      throw string("expected token.");

	if (!matched)	throw s_buf;
	if (_currentToken != '.'){
		throw string ("Missing token '.'");

	
	}
  }
  

  void restDisjunctionMatch() {
	  if (_scanner.currentChar() == '.' && un1==true)
		throw string ("Unexpected ';' before '.'");
	  if (_scanner.currentChar() == '.' && un2==true)
		throw string ("Unexpected ',' before '.'");

    if (_scanner.currentChar() == ';') {
	
      createTerm();
	  
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }

  void disjunctionMatch() {
	
    conjunctionMatch();
    restConjunctionMatch();
  }

  void restConjunctionMatch() {
	  
    if (_scanner.currentChar() == ',') {
	
		
      createTerm();
	
	  if (_scanner.currentChar() == '.')
			throw string("Unexpected ',' before '.'");
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
	  ///////////////
	  

	  ///////////////
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }

  void conjunctionMatch() {
	
    Term * left = createTerm();

    if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
	  matched=true;
    }
	else if (_currentToken ==';'){
		un1=true;
	}
	else if (_currentToken==','){
		un2=true;
	}
	else {
		
		s_buf = ""+left->symbol()+" does never get assignment";
		
	}
  }

  Exp* getExpressionTree(){
    return _expStack.top();
  }
  bool matched=false;
  bool un1=false;
  bool un2=false;
  string s_buf;
private:
  //FRIEND_TEST(ParserTest, createArgs);
  //FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  //FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  //FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  //FRIEND_TEST(ParserTest, createTerms);

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

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;

  vector<Variable *> record;
  
	
};
#endif
