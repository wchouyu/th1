#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"


// TEST(iterator,template_test)
// {
//   Variable X("X");
//   Number one(1);
//   Struct t(Atom("t"),{&X,&one});
//   Iterator<Term*> *it=t.createIterator();
// }

TEST(iterator, struct_first) {
    Variable X("X");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Iterator<Term*>*itStruct = t.createIterator();
    itStruct->first();
    ASSERT_EQ("X", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("2", itStruct->currentItem()->symbol());

    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

//s(1, t(X, 2), Y)
TEST(iterator, struct_nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> *it = s.createIterator();
  it->first();
  it->next();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_FALSE(it->isDone());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_FALSE(it->isDone());
  ASSERT_EQ("Y",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}
//
 TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *it=l.createIterator();
    Iterator<Term*>* itList = it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}
TEST(iterator, secondList) {
    Number one(1);
    Variable Y("Y");
    List l({ &one, &Y });
    Iterator<Term*> *it=l.createIterator();

    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}
// TEST(iterator, NullIterator){
//   Number one(1);
//   NullIterator nullIterator(&one);
//   nullIterator.first();
//   ASSERT_TRUE(nullIterator.isDone());
//   Iterator * it = one.createIterator();
//   it->first();
//   ASSERT_TRUE(it->isDone());
//}
//
// s(1, t(X, 2), Y)
TEST(iterator, structFirstDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
//
//
TEST(iterator, listFirstDFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  // Struct t(Atom("t"), { &X, &two });
  // Struct s(Atom("s"), { &one, &t, &Y });
  List l({&X,&Y,&one,&two});
  List l2({&two,&l,&X});
  Iterator<Term*> *it = l2.createDFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y, 1, 2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
// TEST(iterator, structSecondDFS) {
//   Number one(1);
//   Variable X("X");
//   Variable Y("Y");
//   Number two(2);
//   List l({&X,&Y});
//   Struct t(Atom("t"), { &X, &two,&l });
//   Struct s(Atom("s"), { &one, &t, &Y });
//   Iterator<Term*> *it = s.createDFSIterator();
//   it->first();
//   ASSERT_EQ("1", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("t(X, 2, [X, Y])", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("X", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("2", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("X", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("Y", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("Y", it->currentItem()->symbol());
//   it->next();
//   ASSERT_TRUE(it->isDone());
// }
// //
// TEST(iterator, ListSecondDFS) {
//   Number one(1);
//   Variable X("X");
//   Variable Y("Y");
//   Number two(2);
//   Struct t(Atom("t"), { &X, &two });
//   List l2;
//   List l({&X,&Y, &t, &l2});
//   Iterator<Term*> *it = l.createDFSIterator();
//   it->first();
//   ASSERT_EQ("X", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("Y", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("X", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("2", it->currentItem()->symbol());
//   it->next();
//   ASSERT_EQ("[]", it->currentItem()->symbol());
//   it->next();
//   ASSERT_TRUE(it->isDone());
// }
// s(1, t(X, 2), Y)
TEST(iterator, StructFirstBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

//[2, [X, Y], 1]
TEST(iterator, listFirstBFS) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List l({&X,&Y});
  List l2({&two,&l,&one});
  Iterator<Term*> *it = l2.createBFSIterator();
  it->first();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
#endif
