// Header file for the function that checks if each guess is valid under hard mode.

#ifndef HARDGUESSCHECK_H
#define HARDGUESSCHECK_H

#include <string>
#include <vector>

// Guess state that gets updated after each guess
struct HardModeState {
    std::vector<std::pair<char, int>> greens; //vectors for easy insertion
    std::vector<char> yellows;
};

void updateHardModeState(HardModeState& state, const std::string& guess, const std::string& feedback);

bool isValidHardModeGuess(const std::string& guess, const HardModeState& state);

#endif
