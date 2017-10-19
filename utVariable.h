#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "struct.h"
#include "atom.h"
#include "number.h"


TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X.symbol());
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}

TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
	Variable X("X");
	Number num(2.7182);
	X.match(num);
	ASSERT_EQ("2.7182",X.value());
	
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
	Variable X("X");
	Variable Y("Y");
	Number num(1);

	X.match(Y);
	X.match(num);
	
	ASSERT_EQ("1",Y.value());
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
	Variable X("X");
	Variable Y("Y");
	Number num(1);

	X.match(Y);
	Y.match(num);
	
	ASSERT_EQ("1",X.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
	Variable X("X");
	Number num(1);
	
	X.match(X);
	X.match(num);
	
	ASSERT_EQ("1",X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
	Variable Y("Y");
	Variable X("X");
	Number num(1);
	Y.match(num);
	X.match(Y);
	ASSERT_EQ("1",X.value());
	std::cout << "ut1,";
}


// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
	
	Variable Y("Y");
	Variable X("X");
	Number num(1);
	Y.match(num);
	X.match(Y);
	ASSERT_EQ("1",X.value());
	std::cout << "ut1,";
}


// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
	/*Variable X("X");
	Variable Y("Y");
	Variable Z("Z");
	Number num(1);
	X.match(Y);X.match(Z);Z.match(num);
	ASSERT_EQ("1",X.value());
	ASSERT_EQ("1",Y.value());
	ASSERT_EQ("1",Z.value());*/
}


/*
Variable.varY_to_varX_and_num1_to_varX
Variable.varY_to_varX_and_num1_to_varY
Variable.varX_match_varX_and_num1_to_varX
Variable.num1_to_varZ_to_varY_to_varX
Variable.num1_to_varZ_to_varX_and_varY_to_varX
Variable.varX_to_varY_and_varZ_to_varX_and_num1_to_varZ
Variable.varY_to_varX_and_varW_to_varZ_and_varZ_to_varY_and_num1_to_varY
Variable.Struct2
*/
////////////////////////////////////////////////////////////////

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
/*
TEST (Variable, Struct1) {
	Variable X("X");
	Variable Y("Y");
	std::vector<Term *> v={&X};
	Struct s(Atom("s"),v);
	Y.match(s);
	ASSERT_EQ("Y",Y.symbol());
	ASSERT_EQ("s(X)",Y.value());
	
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
	Variable X("X");Variable Y("Y");
	Atom teddy("teddy");
	std::vector<Term *> v={&X};
	Struct s(Atom("s"),v);

	Y.match(s);
	X.match(teddy);
	ASSERT_EQ("Y",Y.symbol());
	ASSERT_EQ("s(X)",Y.value());
}*/

#endif
