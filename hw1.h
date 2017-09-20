#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;
TEST (Sort, sortByIncreasingPerimeter) {
	Sort s;
	
	Rectangle test_graph1(0,0,1,1);
	Circle test_graph2(0,0,1);
	vertex p1={0,0};
	vertex p2={0,1};
	vertex p3={1,0};
	//Triangle test_graph3({0,0},{0,1},{1,0});
	Triangle test_graph3(p1,p2,p3);
	list<Shape *> *shapeList=new list<Shape *>[3];
	
	/////////////////////////////////
	shapeList[0].push_back(&test_graph1);
	shapeList[1].push_back(&test_graph2);
	shapeList[2].push_back(&test_graph3);
	/////////////////////////////////
	s.sortByIncreasingPerimeter(shapeList);
	//sortByIncreasingPerimeter(shapeList);
	
	//ASSERT_EQ("t",shapeList[0].front()->name);
	//ASSERT_EQ("r",shapeList[1].front()->name);
	//ASSERT_EQ("c",shapeList[2].front()->name);
	
	ASSERT_EQ(&test_graph3,shapeList[0].front());
	ASSERT_EQ(&test_graph1,shapeList[1].front());
	ASSERT_EQ(&test_graph2,shapeList[2].front());
}

TEST (Sort, sortByDecreasingPerimeter) {
	Sort s;
	Rectangle test_graph1(0,0,2,1);
	Circle test_graph2(0,0,2);
	vertex p1={0,0};
	vertex p2={0,1};
	vertex p3={0.5,0};
	//Triangle test_graph3({0,0},{0,1},{1,0});
	Triangle test_graph3(p1,p2,p3);
	list<Shape *> *shapeList=new list<Shape *>[3];
	
	/////////////////////////////////
	shapeList[0].push_back(&test_graph1);
	shapeList[1].push_back(&test_graph2);
	shapeList[2].push_back(&test_graph3);
	/////////////////////////////////
	
	s.sortByDecreasingPerimeter(shapeList);
	
	//ASSERT_EQ("c",shapeList[0].front()->name);
	//ASSERT_EQ("r",shapeList[1].front()->name);
	//ASSERT_EQ("t",shapeList[2].front()->name);
	
	ASSERT_EQ(&test_graph2,shapeList[0].front());
	ASSERT_EQ(&test_graph1,shapeList[1].front());
	ASSERT_EQ(&test_graph3,shapeList[2].front());
}

TEST (Sort, sortByIncreasingArea) {
	Sort s;
	Rectangle test_graph1(0,0,6,6);
	Circle test_graph2(5,6,3);
	vertex p1={5,5};
	vertex p2={6,6};
	vertex p3={4,5};
	//Triangle test_graph3({0,0},{0,1},{1,0});
	Triangle test_graph3(p1,p2,p3);
	list<Shape *> *shapeList=new list<Shape *>[3];
	
	/////////////////////////////////
	shapeList[0].push_back(&test_graph1);
	shapeList[1].push_back(&test_graph2);
	shapeList[2].push_back(&test_graph3);
	/////////////////////////////////
	
	s.sortByIncreasingArea(shapeList);
	
	//ASSERT_EQ("t",shapeList[0].front()->name);
	//ASSERT_EQ("c",shapeList[1].front()->name);
	//ASSERT_EQ("r",shapeList[2].front()->name);
	
	ASSERT_EQ(&test_graph3,shapeList[0].front());
	ASSERT_EQ(&test_graph2,shapeList[1].front());
	ASSERT_EQ(&test_graph1,shapeList[2].front());
}

TEST (Sort, sortByDecreasingArea) {
	Sort s;
	Rectangle test_graph1(1,1,4,1);
	Circle test_graph2(1,2,3);
	vertex p1={2,0};
	vertex p2={0,2};
	vertex p3={2,2};
	//Triangle test_graph3({0,0},{0,1},{1,0});
	Triangle test_graph3(p1,p2,p3);
	list<Shape *> *shapeList=new list<Shape *>[3];
	
	/////////////////////////////////
	shapeList[0].push_back(&test_graph1);
	shapeList[1].push_back(&test_graph2);
	shapeList[2].push_back(&test_graph3);
	/////////////////////////////////
	
	s.sortByDecreasingArea(shapeList);
	
	//ASSERT_EQ("c",shapeList[0].front()->name);
	//ASSERT_EQ("r",shapeList[1].front()->name);
	//ASSERT_EQ("t",shapeList[2].front()->name);
	
	ASSERT_EQ(&test_graph2,shapeList[0].front());
	ASSERT_EQ(&test_graph1,shapeList[1].front());
	ASSERT_EQ(&test_graph3,shapeList[2].front());
}

TEST (Sort, sortByIncreasingCompactness) {
	Sort s;
	Rectangle test_graph1(0,0,1,1);
	Circle test_graph2(0,0,1);
	vertex p1={0,0};
	vertex p2={0,1};
	vertex p3={1,0};
	//Triangle test_graph3({0,0},{0,1},{1,0});
	Triangle test_graph3(p1,p2,p3);
	list<Shape *> *shapeList=new list<Shape *>[3];
	
	/////////////////////////////////
	shapeList[0].push_back(&test_graph1);
	shapeList[1].push_back(&test_graph2);
	shapeList[2].push_back(&test_graph3);
	/////////////////////////////////
	s.sortByIncreasingCompactness(shapeList);
	//ASSERT_EQ("t",shapeList[0].front()->name);
	//ASSERT_EQ("r",shapeList[1].front()->name);
	//ASSERT_EQ("c",shapeList[2].front()->name);
	// Compactness = area/perimeter
	ASSERT_EQ(&test_graph3,shapeList[0].front());
	ASSERT_EQ(&test_graph1,shapeList[1].front());
	ASSERT_EQ(&test_graph2,shapeList[2].front());
	
}

#endif
