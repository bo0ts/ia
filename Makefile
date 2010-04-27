OBJS = ItemSet.o ItemSetContainer.o main.o
CXX = g++
DEBUG = -g
OPTI = -O0
CXXFLAGS = -Wall -Wextra -c $(DEBUG) $(OPTI)
LFLAGS = -lboost_program_options $(DEBUG) $(OPTI)

main: $(OBJS) 
	$(CXX) $(LFLAGS) $(OBJS) -o main

.PHONY: clean
clean:
	rm -f *.o test main

test: ItemSetTest.o ItemSet.o
	$(CC) -lboost_unit_test_framework ItemSetTest.o ItemSet.o -o test && ./test

ItemSetTest.o: ItemSetTest.cpp ItemSet.hh

main.o: main.cpp ItemSetContainer.hh

ItemSet.o: ItemSet.cpp ItemSet.hh

ItemSetContainer.o: ItemSetContainer.cpp ItemSetContainer.hh ItemSet.hh