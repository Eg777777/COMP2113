#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD
};

void setCurrentDifficulty(Difficulty diff);

std::string getRandomWordByDifficulty();

#endif
