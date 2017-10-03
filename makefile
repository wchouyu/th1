all: madRace utAtom utVariable hw2
#all: hw2
madRace: mainMadRace.o
		g++ -o madRace mainMadRace.o -lgtest 
mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

utAtom: mainAtom.o
		g++ -o utAtom mainAtom.o -lgtest -lpthread	
mainAtom.o: mainAtom.cpp utAtom.h atom.h atom.cpp
	g++ -std=gnu++0x -c mainAtom.cpp	
	
utVariable: mainVariable.o
		g++ -o utVariable mainVariable.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h variable.cpp
		g++ -std=gnu++0x -c mainVariable.cpp

hw2: mainTerm.o mainVariable.o mainAtom.o mainMadRace.o
		g++ -o hw2 mainTerm.o -lgtest -lpthread
mainTerm.o:	mainTerm.cpp utTerm.h number.h number.cpp
		g++ -std=gnu++0x -c mainTerm.cpp



clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif

#clean:
#	rm -f *.o madRace utAtom
#stat:
#	wc *.h *.cpp
