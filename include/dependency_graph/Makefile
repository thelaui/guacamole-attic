CC = g++-4.6
BI = /opt/boost/current/include/
BL = /opt/boost/current/lib/
test: test.cpp Field.hpp DataField.hpp
	$(CC) test.cpp -otest -std=c++0x -I. -I$(BI) -L$(BL) -lboost_unit_test_framework
