#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle test_graph1(0,0,1,1);
	Circle test_graph2(0,0,1);
	vertex p1={0,0};
	vertex p2={0,1};
	vertex p3={1,0};
	//Triangle test_graph3({0,0},{0,1},{1,0})
	Triangle test_graph3(p1,p2,p3);
	std::<Shape *> * shapeList;
	shapeList
	sortByIncreasingPerimeter()
	EXPECT_EQ(,)
}

TEST (Sort, sortByDecreasingPerimeter) {

}

TEST (Sort, sortByIncreasingArea) {

}

TEST (Sort, sortByDecreasingArea) {

}

TEST (Sort, sortByIncreasingCompactness) {

}

#endif
