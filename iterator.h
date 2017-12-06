#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"

#include <queue>
using namespace std;

//T=*Term


template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T  currentItem() const  = 0;
  virtual bool isDone() const = 0;
};


class NullIterator :public Iterator<Term*>{
public:
  NullIterator(Term* n){}
  void first(){}
  void next(){}
  Term* currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

class StructIterator:public Iterator<Term*>
{
public:
  friend class Struct;
  StructIterator(Struct *s): _index(0), _s(s) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:

  int _index;
  Struct* _s;
};

class ListIterator :public Iterator<Term*>{
public:
  ListIterator(List *list): _index(0), _list(list) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

class DFSIterator:public Iterator<Term*>{
public:

  DFSIterator(Term *term): _index(0),_term(term){}
  void first(){
    _index=1;
    _terms.clear();
    DFS(_term);
  }
  void DFS(Term *term){
    _terms.push_back(term);
    Struct *ps=dynamic_cast<Struct*>(term);
    List*pl=dynamic_cast<List*>(term);
    if (ps){
      for(int i=0;i<ps->arity();i++)
        DFS(ps->args(i));
    }
    if (pl){
      for (int i=0;i<pl->arity();i++)
        DFS(pl->args(i));
    }
  }

  Term* currentItem() const {
  return _terms[_index];
}
  void next(){
    _index++;
  }
  bool isDone() const{
    return _index>=_terms.size()-1;
  }
private:
  int _index;
  Term *_term;
  std::vector<Term*>_terms;
};

class BFSIterator:public Iterator<Term*>{
public:
  BFSIterator(Term *term):_index(0),_term(term){}
  void first(){
    _index=1;
    _terms.clear();
    BFS(_term);
  }
  void BFS(Term*term){
    queue<Term*>q;
    q.push(_term);
    while(!q.empty()){
      Term *n=q.front();
      q.pop();
      _terms.push_back(n);
      Struct *ps=dynamic_cast<Struct*>(n);
      List*pl=dynamic_cast<List*>(n);
      if(ps){
        for(int i=0;i<ps->arity();i++)
          q.push(ps->args(i));
      }
      else if(pl){
        for(int i=0;i<pl->arity();i++)
          q.push(pl->args(i));
      }
    }
  }
  Term * currentItem()const{
    return _terms[_index];
  }
  bool isDone()const{
    return _index>=_terms.size()-1;
  }
  void next(){
    _index++;
  }
private:
  int _index=0;
  Term*_term;
  std::vector<Term*>_terms;

};

#endif
