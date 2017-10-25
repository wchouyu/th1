#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
	List l;
	ASSERT_EQ("[]",l.symbol());
}

// Given there are two perfect numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
	Number num(8128);Number num2(496);
	vector<Term*>v={&num,&num2};
	List l(v);
	ASSERT_EQ("[8128, 496]",l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao"); Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term*>v={&terence_tao,&alan_mathison_turing};
	List l(v);
	ASSERT_EQ("[terence_tao, alan_mathison_turing]",l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X");Variable Y("Y");
	vector<Term*>v={&X,&Y};
	List l(v);
	ASSERT_EQ("[X, Y]",l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom");Number num(496);Variable X("X");Atom terence_tao("terence_tao");
	vector<Term*>v={&num,&X,&terence_tao};
	List l(v);
	ASSERT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number num(8128);Number num2(496);Variable X("X");Atom terence_tao("terence_tao");
	vector<Term*>v={&num2,&X,&terence_tao};
	List l(v);
	ASSERT_FALSE(num.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Variable X("X");Number num(496);Atom terence_tao("terence_tao");
	vector<Term*>v1={&X};
	vector<Term*>v2={&num,&X,&terence_tao};
	Struct s(Atom("s"),v1);
	List l(v2);
	ASSERT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Variable Y("Y");
	Number num(496);Variable X("X");Atom terence_tao("terence_tao");
	vector<Term*>v={&num,&X,&terence_tao};
	List l(v);
	//Y.match(l);
	ASSERT_TRUE(Y.match(l));
	ASSERT_EQ("[496, X, terence_tao]",Y.value());
}

// ?- X = [496, X, terence_tao].
// false. //Don't care
TEST(List, matchToVarOccuredInListShouldFail) {
	Variable X("X");
	Number num(496);Atom terence_tao("terence_tao");
	vector<Term*>v={&num,&X,&terence_tao};
	List l(v);X.match(l);
	ASSERT_EQ("X",X.value());
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Variable X("X");
	Number num(496);Atom terence_tao("terence_tao");
	vector<Term*>v={&num,&X,&terence_tao};
	List l(v);
	ASSERT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Variable X("X");Variable Y("Y");
	Number num(496);Atom terence_tao("terence_tao");
	vector<Term*>v1={&num,&X,&terence_tao};
	vector<Term*>v2={&num,&Y,&terence_tao};
	List l1(v1);List l2(v2);
	ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	
	Variable X("X");Number num8128(8128);
	Number num496(496);Atom terence_tao("terence_tao");
	vector<Term*>v1={&num496,&X,&terence_tao};
	vector<Term*>v2={&num496,&num8128,&terence_tao};
	List l1(v1);List l2(v2);
	//l1.match(l2);
	ASSERT_TRUE(l1.match(l2));
	ASSERT_TRUE(l2.match(l1));
	ASSERT_EQ("8128",X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {

	Variable X("X");Number num(496);Atom terence_tao("terence_tao");
	vector<Term*>v={&num,&X,&terence_tao};
	List l(v);Variable Y("Y");Atom alan_mathison_turing("alan_mathison_turing");

	Y.match(l);

	X.match(alan_mathison_turing);
	ASSERT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
	ASSERT_EQ("alan_mathison_turing",X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  
  EXPECT_EQ(string("first"), l.head()->symbol());
 
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("[first]"), s("second"), t("third");
	vector<Term *> args = {&f, &s, &t};
	List l(args);
	EXPECT_EQ("[first]",l.head()->value());
	EXPECT_EQ("[second, third]",l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("[first]"), s("second"), t("third");
	vector<Term *> args = {&f, &s, &t};
	List l(args);
	EXPECT_EQ("third",l.tail()->tail()->head()->value());
	EXPECT_EQ("[]",l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
	List l;
	try {
		l.head(); 
    }
    catch(std::out_of_range const & err) {
        EXPECT_EQ(std::string("Accessing head in an empty list"),err.what());
    }
	
	

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
	List l;
	try{
		l.tail();}
	catch(std::out_of_range const &err){
		EXPECT_EQ(std::string("Accessing tail in an empty list"),err.what());
		throw std::string("Accessing tail in an empty list");
	}
	
}




#endif
