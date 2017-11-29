#ifndef NODE_H
#define NODE_H

#include "atom.h"
#include "variable.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
  
  bool evaluate()
  {
	  if (right == NULL) std::cout<<"error\n";
	  if (payload==SEMICOLON){//std::cout << "here\n";
		  return left->evaluate()||right->evaluate();
	  }
	  else if (payload==COMMA){//std::cout << "here2\n";
		  return left->evaluate()&&right->evaluate();
	  }
	  else if (payload==EQUALITY){//std::cout << "here3\n";
		  std::cout << left->term->symbol() << "\n";
		  std::cout << right->term->symbol() << "\n";
		  return left->term->match(*right->term);

	  }
  };

public:
	Operators payload;
	Term * term;
	Node * left;
	Node * right;
	
};

#endif
