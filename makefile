# ID: *****1536
# EMAIL: yairjacob620@gmail.com

COM = g++ -Wall
H = tree_classes.hpp

tree: main
	./main

main: main.cpp $(H)
	$(COM) main.cpp -o main

test: tests.o $(H) complex.hpp
	$(COM) tests.o -o tests
	./tests

tests.o: tests.cpp # doctest.h 
	$(COM) -c tests.cpp

clean:
	rm *.o *.exe
