INC_DIR = include

all: hw2

hw2: main.o atom.o number.o variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest
else
	g++ -o hw2 main.o atom.o number.o variable.o -lgtest -lpthread
endif
	
main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp
atom.o: $(INC_DIR)/atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
number.o: $(INC_DIR)/number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
variable.o: $(INC_DIR)/variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
