#include "difficulty.h"
#include "wordLists.h"
#include <cstdlib>

static Difficulty currentDifficulty = Difficulty::MEDIUM;

void setCurrentDifficulty(Difficulty diff) {
    currentDifficulty = diff;
}

std::string getRandomWordByDifficulty() {
    size_t total = wordList.size();
    if (total == 0) {
        return "apple";
    }

    size_t start = 0, end = 0;
    switch (currentDifficulty) {
        case Difficulty::EASY:
            start = 0;
            end = total / 3;
            break;
        case Difficulty::MEDIUM:
            start = total / 3;
            end = 2 * total / 3;
            break;
        case Difficulty::HARD:
            start = 2 * total / 3;
            end = total;
            break;
        default:
            start = 0;
            end = total;
            break;
    }

    if (start >= end) {
        start = 0;
        end = total;
    }

    size_t index = start + rand() % (end - start);
    return wordList[index];
}
