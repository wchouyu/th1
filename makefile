all: hw5 

hw5: main.o atom.o global.h list.o parser.h scanner.h struct.h variable.h
ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o -lgtest
else
	g++ -o hw5 main.o -lgtest -pthread
endif


main.o: main.cpp utVariable.h
	g++ --std=gnu++0x -c main.cpp
atom.o: atom.h atom.cpp
	g++ --std=gnu++0x -c atom.cpp
	
list.o: list.h list.cpp
	g++ --std=gnu++0x -c list.cpp



clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp