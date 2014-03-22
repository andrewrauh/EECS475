CC = g++
LD = g++

CFLAGS = -c -pedantic -std=c++11 -Wall
LFLAGS = -pedantic -Wall -O3 

OBJS = Montgomery.o Homework4.o uberzahl.o main.o
PROG = Homework4

all: $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

debug: CFLAGS += -g -DDEBUG
debug: all

main.o: main.cpp Homework4.cpp uberzahl/uberzahl.h
	$(CC) $(CFLAGS) main.cpp

Montgomery.o: Montgomery.cpp Montgomery.h uberzahl/uberzahl.h
	$(CC) $(CFLAGS) Montgomery.cpp

Homework4.o: Homework4.cpp Homework4.h Montgomery.h uberzahl/uberzahl.h
	$(CC) $(CFLAGS) Homework4.cpp

uberzahl.o: uberzahl/uberzahl.cpp uberzahl/uberzahl.h
	$(CC) $(CFLAGS) uberzahl/uberzahl.cpp

clean:
	rm -f *.o $(PROG)
	rm -f uberzahl/*.o

