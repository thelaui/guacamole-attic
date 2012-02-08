CC = g++-4.6
BI = /usr/include/ 
BL = /usr/lib/
SRCPATH = ../../../src/dependency_graph/
INCPATH = ../

%.o: $(SRCPATH)%.cpp $(INCPATH)%.hpp
	$(CC) -c $< -I$(INCPATH) -std=c++0x 

test: test.cpp $(INCPATH)SingleField.hpp adder.hpp FieldContainer.o Field.o
	$(CC) -c test.cpp -std=c++0x -I$(INCPATH) -I$(BI)
	$(CC) test.o FieldContainer.o Field.o -otest -std=c++0x  -L$(BL) -lboost_unit_test_framework


