# ID: *****1536
# EMAIL: yairjacob620@gmail.com

ifeq ($(OS),Windows_NT)
	COMP = g++
else
	COMP = clang++
endif
FLA = -Wall
H = tree_classes.hpp

tree: main
	./main

main: main.cpp $(H)
	$(COMP) $(FLA) main.cpp -o main

test: tests.o $(H) complex.hpp
	$(COMP) $(FLA) tests.o -o tests
	./tests

tests.o: tests.cpp doctest.h 
	$(COMP) $(FLA) -c tests.cpp

clean:
	rm *.o *.exe
