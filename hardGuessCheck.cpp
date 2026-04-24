// Functions for Checking Hard Mode Guesses

#include "hardGuessCheck.h"

#include <string>
#include <vector>

/*
struct HardModeState {
    std::vector<std::pair<char, int>> greens; //vectors for easy insertion
    std::vector<char> yellows;
};
*/

// Updates the state of hard mode based on the "result" from latest guesses
void updateHardModeState(HardModeState& state, const std::string& guess, const std::string& feedback) {
    for (int i = 0; i < 5; i++) {
        if (feedback[i] == 'G') {
            bool knownGreen = false;
            for (const std::pair<char, int>& green : state.greens) {
                if (green.second == i) {
                    knownGreen = true;
                    break;
                }
            }
            if (!knownGreen) {
                state.greens.push_back({guess[i], i});
            }
        }
        else if (feedback[i] == 'Y') {
            bool knownYellow = false;
            for (const char& yellow : state.yellows) {
                if (yellow == guess[i]) {
                    knownYellow = true;
                    break;
                }
            }
            if (!knownYellow) {
                state.yellows.push_back(guess[i]);
            }
        }
    }
}

// Compares player guess to current state under hard mode rules
bool isValidHardModeGuess(const std::string& guess, const HardModeState& state) {
    //Check Greens. Positions must match
    for (const std::pair<char, int>& green : state.greens) {
        if (guess[green.second] != green.first) {
            return false;
        }
    }
    //Check Yellows. Letters must at least exist
    for (const char& yellow : state.yellows) {
        if (guess.find(yellow) == std::string::npos) {
            return false;
        }
    }
    return true;
}


