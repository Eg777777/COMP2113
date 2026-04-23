#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Word list for the game
vector<string> wordList = {
    "apple", "grape", "storm", "plant", "dream",
    "music", "dance", "paint", "sunny", "throw",
    "bread", "water", "green", "stone", "party",
    "chess", "brain", "heart", "ocean", "flame"
};

string getRandomWord() {
    return wordList[rand() % wordList.size()];
}

string checkGuess(const string& targetWord, const string& guess) {
    string result(5, ' ');
    vector<bool> targetUsed(5, false);
    vector<bool> guessProcessed(5, false);

    // First pass: check for correct positions (G)
    for (int i = 0; i < 5; i++) {
        if (guess[i] == targetWord[i]) {
            result[i] = 'G';
            targetUsed[i] = true;
            guessProcessed[i] = true;
        }
    }

    // Second pass: check for correct letters in wrong positions (Y)
    for (int i = 0; i < 5; i++) {
        if (!guessProcessed[i]) {
            bool found = false;
            for (int j = 0; j < 5; j++) {
                if (!targetUsed[j] && guess[i] == targetWord[j]) {
                    result[i] = 'Y';
                    targetUsed[j] = true;
                    found = true;
                    break;
                }
            }
            if (!found) {
                result[i] = 'X';  // Letter not in word
            }
        }
    }

    return result;
}

void playGame() {
    string targetWord = getRandomWord();
    string guess;
    int attempts = 6;
    int attemptCount = 0;

    cout << "\n=== Wordle Game ===" << endl;
    cout << "Guess the 5-letter word. You have " << attempts << " attempts." << endl;
    cout << "Feedback: G = correct position, Y = correct letter wrong position, X = not in word" << endl;
    cout << "--------------------------------" << endl;

    while (attemptCount < attempts) {
        cout << "\nAttempt " << (attemptCount + 1) << "/" << attempts << ": ";
        cout.flush();
        
        if (!(cin >> guess)) {
            if (cin.eof()) {
                cout << "\nGame ended (EOF)." << endl;
                return;
            }
            cin.clear();
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        // Validate input
        if (guess.length() != 5) {
            cout << "Please enter exactly 5 letters." << endl;
            continue;
        }

        // Convert to lowercase
        transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

        // Check if all characters are alphabetic
        bool validInput = true;
        for (char c : guess) {
            if (!isalpha(c)) {
                validInput = false;
                break;
            }
        }

        if (!validInput) {
            cout << "Please enter only alphabetic characters." << endl;
            continue;
        }

        string feedback = checkGuess(targetWord, guess);
        cout << "Feedback: " << feedback << endl;

        if (guess == targetWord) {
            cout << "\nCongratulations! You guessed the word: " << targetWord << endl;
            return;
        }

        attemptCount++;
    }

    cout << "\n❌ Game Over! The word was: " << targetWord << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        playGame();

        cout << "\nDo you want to play again? (y/n): ";
        if (!(cin >> playAgain)) {
            // EOF reached, exit gracefully
            break;
        }
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
