CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib

all: Go

Go: bin/Card.o bin/Deck.o bin/Hand.o bin/Player.o bin/Game.o bin/reviiot.o
	$(CC) -o bin/reviiot bin/Card.o bin/Deck.o bin/Hand.o bin/Player.o bin/Game.o bin/reviiot.o $(LFLAGS)

bin/Card.o: src/Card.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Card.o src/Card.cpp

bin/Deck.o: src/Deck.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Deck.o src/Deck.cpp

bin/Hand.o: src/Hand.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Hand.o src/Hand.cpp

bin/Player.o: src/Player.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Player.o src/Player.cpp


bin/Game.o: src/Game.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Game.o src/Game.cpp


bin/reviiot.o: src/reviiyot.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/reviiot.o src/reviiyot.cpp

clean:
	rm -f bin/*
