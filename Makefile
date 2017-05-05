CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

chess: Chess.o Board.o main.o
	$(CXX) $(CXXFLAGS) Chess.o Board.o main.o -o chess

unittest: Chess.o Board.o unittest.o
	$(CXX) $(CXXFLAGS) Chess.o Board.o unittest.o -o unittest

unittest.o: Game.h Chess.h Prompts.h
main.o: Game.h Chess.h Prompts.h
Board.o: Game.h
Chess.o: Game.h Chess.h Prompts.h

clean:
	rm *.o chess

