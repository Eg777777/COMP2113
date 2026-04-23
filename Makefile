wordle: wordle.o
	g++ -pedantic-errors -std=c++11 wordle.o -o gradecounter

wordle.o: wordle.cpp
	g++ -pedantic-errors -std=c++11 -c wordle.cpp

clean:
	rm -f wordle wordle.o

.PHONY: clean
