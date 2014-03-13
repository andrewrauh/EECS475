all:
	g++ -pedantic -std=c++11 -DNDEBUG -Wall -O3 main.cpp Homework4.cpp Montgomery.cpp -lgmpxx -lgmp -o homework4

debug:
	g++ -pedantic -std=c++11 -DDEBUG -Wall -g main.cpp Homework4.cpp Montgomery.cpp -lgmpxx -lgmp -o homework4

clean:
	rm -f *.o homework4

