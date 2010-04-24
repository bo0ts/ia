OBJS = ItemSet.o ItemSetContainer.o main.o
CC = g++
DEBUG = -g
OPTI = -O4
CFLAGS = -Wall -c $(DEBUG) $(OPTI)
LFLAGS = -Wall $(DEBUG) $(OPTI)

main: $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o main

.PHONY: clean
clean:
	rm *.o test main

test: ItemSetTest.o ItemSet.o
	$(CC) -lboost_unit_test_framework ItemSetTest.o ItemSet.o -o test && ./test

ItemSetTest.o: ItemSetTest.cpp ItemSet.hh

main.o: main.cpp ItemSetContainer.hh

ItemSet.o: ItemSet.cpp ItemSet.hh

ItemSetContainer.o: ItemSetContainer.cpp ItemSetContainer.hh ItemSet.hh