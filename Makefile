OBJS = ItemSetContainer.o main.o
CXX = g++
DEBUG = -g
OPTI = -O4
CXXFLAGS = -Wall -Wextra -Wno-inline -pedantic -pedantic-errors -std=c++0x -g -pg -c $(DEBUG) $(OPTI)
LFLAGS = -lboost_program_options -pg $(DEBUG) $(OPTI)

main: $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o main

.PHONY: clean
clean:
	rm -f *.o test main

test: ItemSetTest.o ItemSet.hh
	$(CC) -lboost_unit_test_framework ItemSetTest.o -o test && ./test

ItemSetTest.o: ItemSetTest.cpp ItemSet.hh

main.o: main.cpp ItemSetContainer.hh

ItemSetContainer.o: ItemSetContainer.cpp ItemSetContainer.hh ItemSet.hh