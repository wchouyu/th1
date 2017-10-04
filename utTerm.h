#ifndef UTTERM_H
#define UTTERM_H

#include "atom.h"
#include "variable.h"
#include "number.h"

//test Number.value()
TEST (Number,ctor) {
	Number num_25(25);
	ASSERT_EQ("25",num_25.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number num_25(25);
	ASSERT_EQ("25",num_25.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number num_25(25);
	Number num_25_2(25);
	ASSERT_TRUE(num_25.match(num_25_2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number num_25(25);
	Number num_0(0);
	ASSERT_FALSE(num_25.match(num_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number num_25(25);
	Atom tom("tom");
	ASSERT_FALSE(num_25.match(tom));
}

//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
	Number num_25(25);
	Variable X("X");
	num_25.match(X);
	ASSERT_EQ("25",X.value());
}

//?- tom=25.
//false.

TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number num_25(25);
	ASSERT_FALSE(tom.match(num_25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X("X");
	tom.match(X);
	ASSERT_EQ("tom",X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	tom.match(X);
	ASSERT_EQ("tom",X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom jerry("jerry");
	Atom tom("tom");
	X.match(jerry);
	ASSERT_FALSE(tom.match(X));
}


// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
	Variable X("X");
	Number num_5(5);
	X.match(num_5);
	ASSERT_EQ("5",X.value());
}

// ?- X=25, X= 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number num_25(25);
	Number num_100(100);
	X.match(num_25);
	ASSERT_FALSE(X.match(num_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number num_25(25);
	X.match(tom);
	ASSERT_FALSE(X.match(num_25));
}
//?- tom=X, 25=X.
//false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
	Atom tom("tom");
	Variable X("X");
	Number num_25(25);
	tom.match(X);
	ASSERT_FALSE(num_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	X.match(tom);
	ASSERT_TRUE(X.match(tom));
}


#endif