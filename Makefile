all: wordle

wordle: wordle.o hardGuessCheck.o difficulty.o
	g++ -pedantic-errors -std=c++11 wordle.o hardGuessCheck.o difficulty.o -o wordle

wordle.o: wordle.cpp hardGuessCheck.h wordLists.h difficulty.h
	g++ -pedantic-errors -std=c++11 -c wordle.cpp

hardGuessCheck.o: hardGuessCheck.cpp hardGuessCheck.h
	g++ -pedantic-errors -std=c++11 -c hardGuessCheck.cpp

difficulty.o: difficulty.cpp difficulty.h wordLists.h
	g++ -pedantic-errors -std=c++11 -c difficulty.cpp

clean:
	rm -f wordle wordle.o hardGuessCheck.o difficulty.o

.PHONY: clean
