all:
	g++ -pedantic -std=c++11 -Wall -g homework4.cpp -lgmpxx -lgmp -o homework4

clean:
	rm -f *.o homework4

