default: 

.PHONY: clean
clean:
	rm *.o test

test: Test.o ItemSet.o
	g++ -lboost_unit_test_framework Test.o ItemSet.o -o test && ./test

Test.o: Test.cpp ItemSet.hh

ItemSet.o: ItemSet.cpp ItemSet.hh