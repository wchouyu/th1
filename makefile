all:hw8 shell


shell: shell.o atom.o list.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o atom.o list.o struct.o -lgtest 
else
	g++ -o shell shell.o atom.o list.o struct.o -lgtest -lpthread
endif


shell.o: shell.cpp
		g++ -std=gnu++0x -c shell.cpp

hw8: main.o atom.o list.o struct.o
ifeq (${OS}, Windows_NT)
	g++ -o hw8 main.o atom.o list.o struct.o -lgtest 
else
	g++ -o hw8 main.o atom.o list.o struct.o -lgtest -lpthread
endif
main.o: main.cpp  exception.h expression.h
		g++ -std=gnu++0x -c main.cpp 


utAtom: mainAtom.o list.o atom.o struct.o
	g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o struct.o
		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp



		
exp: mainExp.o
	g++ -o exp mainExp.o -lgtest -lpthread
mainExp.o: mainExp.cpp exp.h global.h
	g++ --std=gnu++0x -c mainExp.cpp

utScanner: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h
		g++ --std=gnu++0x -c mainScanner.cpp
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread


mainIterator.o: mainIterator.cpp utIterator.h
	g++ --std=gnu++0x -c mainIterator.cpp


	

clean:
	rm -f *.o  utAtom utVariable utScanner hw8 shell
stat:
	wc *.h *.cpp
