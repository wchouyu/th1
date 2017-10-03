#include "include/Sort.h"
#include <iostream>
#include <algorithm>  

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
	int size = sizeof(*shapeList)/sizeof(shapeList[0].front());
	
	for (int i = 0 ; i < size ;i++)
		for (int j=0;j<size -1-i;j++)
			if (shapeList[j].front()->perimeter() > shapeList[j+1].front()->perimeter())
				swap(shapeList[j],shapeList[j+1]);
				
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
	int size = sizeof(*shapeList)/sizeof(shapeList[0].front());
	
	for (int i = 0 ; i < size ;i++)
		for (int j=0;j<size -1-i;j++)
			if (shapeList[j].front()->perimeter() < shapeList[j+1].front()->perimeter())
				swap(shapeList[j],shapeList[j+1]);
				
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
		int size = sizeof(*shapeList)/sizeof(shapeList[0].front());
	
	for (int i = 0 ; i < size ;i++)
		for (int j=0;j<size -1-i;j++)
			if (shapeList[j].front()->area() > shapeList[j+1].front()->area())
				swap(shapeList[j],shapeList[j+1]);
				
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
			int size = sizeof(*shapeList)/sizeof(shapeList[0].front());
	
	for (int i = 0 ; i < size ;i++)
		for (int j=0;j<size -1-i;j++)
			if (shapeList[j].front()->area() < shapeList[j+1].front()->area())
				swap(shapeList[j],shapeList[j+1]);
				
}
  
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
				int size = sizeof(*shapeList)/sizeof(shapeList[0].front());
	
	for (int i = 0 ; i < size ;i++)
		for (int j=0;j<size -1-i;j++)
			if ((shapeList[j].front()->area()/shapeList[j].front()->perimeter()) 
				> (shapeList[j+1].front()->area()/shapeList[j].front()->perimeter()))
				swap(shapeList[j],shapeList[j+1]);
}
  