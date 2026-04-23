# Wordle Game

## Team members

Leung Cheuk Hang (3036600284), Pang Ching Nam Bosco (3036529806), 

## Application Description

A command-line implementation of the popular word-guessing game Wordle, written in C++. Players have 6 attempts to guess a random 5-letter word from a predefined word list. After each guess, the game provides feedback indicating which letters are correct and in the right position, which letters exist in the word but in the wrong position, and which letters are not in the word at all.

## Features

- **6 Attempts**: Players get 6 chances to guess the correct word before game over
- **Feedback System**: 
  - `G` = Letter is correct and in the right position
  - `Y` = Letter exists in the word but in the wrong position
  - `X` = Letter is not in the word
- **Input Validation**: 
  - Ensures guesses are exactly 5 characters long
  - Accepts only alphabetic characters
  - Converts input to lowercase automatically
- **Replay Option**: Players can choose to play multiple rounds without restarting the program
- **20-Word Vocabulary**: Balanced word selection including common words from various categories
- **Graceful EOF Handling**: Properly exits when EOF is encountered

## Non-Standard Libraries

This application uses **only standard C++ libraries**:
- `<iostream>` - Input/output operations
- `<vector>` - Dynamic word list storage
- `<string>` - String manipulation
- `<cstdlib>` - Random number generation
- `<ctime>` - Seed for randomization
- `<algorithm>` - String transformation utilities

No external dependencies are required.

## Compilation & Execution

### Prerequisites
- A C++ compiler supporting C++11 or later (e.g., g++, clang++)

### Compilation

```bash
g++ -o wordle wordle.cpp
```

Or with optimizations:

```bash
g++ -O2 -o wordle wordle.cpp
```

### Execution

```bash
./wordle
```

### Example Gameplay

```
=== Wordle Game ===
Guess the 5-letter word. You have 6 attempts.
Feedback: G = correct position, Y = correct letter wrong position, X = not in word
--------------------------------

Attempt 1/6: crane
Feedback: YY   X

Attempt 2/6: stone
Feedback: G G X G X

Attempt 3/6: plant
Feedback: G G G G G

Congratulations! You guessed the word: plant

Do you want to play again? (y/n): n
Thanks for playing!
```

---

**Course:** COMP2113
