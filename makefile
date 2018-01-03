all:hw8 shell


shell: shell.o atom.o list.o struct.o
		g++ -o shell shell.o atom.o list.o struct.o -lgtest -pthread
shell.o: shell.cpp
		g++ --std=gnu++0x -c shell.cpp

hw8: main.o atom.o list.o struct.o
		g++ -o hw8 main.o atom.o list.o struct.o -lgtest -pthread
main.o: main.cpp  exception.h
		g++ --std=gnu++0x -c main.cpp


utAtom: mainAtom.o list.o atom.o struct.o
	g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
	g++ --std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ --std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o struct.o
		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ --std=gnu++0x -c mainVariable.cpp
list.o:list.cpp list.h
		g++ --std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ --std=gnu++0x -c struct.cpp



		
#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

utScanner: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h
		g++ --std=gnu++0x -c mainScanner.cpp
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread


mainIterator.o: mainIterator.cpp utIterator.h
	g++ --std=gnu++0x -c mainIterator.cpp


	
#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o  utAtom utVariable utScanner 
stat:
	wc *.h *.cpp
