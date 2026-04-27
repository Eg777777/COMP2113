#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include "hardGuessCheck.h"
#include "wordLists.h"
#include "difficulty.h"

using namespace std;

namespace {

const char* const kStatsFile = "wordle_stats.txt";

struct Statistics {
    int played = 0;
    int wins = 0;
    int currentStreak = 0;
    int maxStreak = 0;
    int dist[6] = {0, 0, 0, 0, 0, 0};
};

struct GameResult {
    bool gameFinished;
    bool won;
    int numGuesses;
    GameResult() : gameFinished(false), won(false), numGuesses(0) {}
    GameResult(bool f, bool w, int g) : gameFinished(f), won(w), numGuesses(g) {}
};

void loadStats(Statistics& s) {
    ifstream in(kStatsFile);
    if (!in) return;
    in >> s.played >> s.wins >> s.currentStreak >> s.maxStreak;
    for (int i = 0; i < 6; i++) in >> s.dist[i];
}

void saveStats(const Statistics& s) {
    ofstream out(kStatsFile);
    if (!out) return;
    out << s.played << " " << s.wins << " " << s.currentStreak << " " << s.maxStreak << "\n";
    for (int i = 0; i < 6; i++) {
        if (i) out << " ";
        out << s.dist[i];
    }
    out << "\n";
}

void updateStats(Statistics& s, const GameResult& r) {
    if (!r.gameFinished) return;
    s.played++;
    if (r.won) {
        s.wins++;
        s.currentStreak++;
        if (s.currentStreak > s.maxStreak) s.maxStreak = s.currentStreak;
        if (r.numGuesses >= 1 && r.numGuesses <= 6)
            s.dist[r.numGuesses - 1]++;
    } else {
        s.currentStreak = 0;
    }
}

int winPercent(int played, int wins) {
    if (played <= 0) return 0;
    return (100 * wins + played / 2) / played;
}

void printStatistics(const Statistics& s) {
    cout << "\n--- STATISTICS ---" << endl;
    int pct = winPercent(s.played, s.wins);
    cout << "Played: " << s.played
         << "   Win %: " << pct
         << "   Current Streak: " << s.currentStreak
         << "   Max Streak: " << s.maxStreak << endl;
}

void printGuessDistribution(const Statistics& s, int highlightNumGuesses) {
    const int kBarMax = 20;
    int maxC = 0;
    for (int i = 0; i < 6; i++) if (s.dist[i] > maxC) maxC = s.dist[i];
    if (maxC < 1) maxC = 1;

    const char* reset = "\033[0m";
    const char* green = "\033[32;1m";
    const char* gray = "\033[90m";

    cout << "\nGUESS DISTRIBUTION" << endl;
    for (int i = 0; i < 6; i++) {
        int label = i + 1;
        int count = s.dist[i];
        int barLen = (count == 0) ? 1 : (count * kBarMax) / maxC;
        if (barLen < 1) barLen = 1;
        if (barLen > kBarMax) barLen = kBarMax;
        bool hi = (highlightNumGuesses == label);
        const char* barColor = hi ? green : gray;
        string barStr(barLen, '#');
        cout << label << "  " << barColor << barStr << " " << count << reset << endl;
    }
}

}

void hint(string word, vector<char> green) {
    for (int i = 0; i < 5; i++) {
        bool alrGuessed = false;
        for (char c : green) {
            if (word[i] == c) { alrGuessed = true; break; }
        }
        if (!alrGuessed) {
            cout << "The letter in position " << i+1 << " is " << word[i] << endl;
            return;
        }
    }
}

string checkGuess(const string& targetWord, const string& guess,
    vector<char>& green, vector<char>& yellow, vector<char>& gray) {
    string result(5, ' ');
    vector<bool> targetUsed(5, false);
    vector<bool> guessProcessed(5, false);
    for (int i = 0; i < 5; i++) {
        if (guess[i] == targetWord[i]) {
            green.push_back(guess[i]);
            result[i] = 'G';
            targetUsed[i] = true;
            guessProcessed[i] = true;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (!guessProcessed[i]) {
            bool found = false;
            for (int j = 0; j < 5; j++) {
                if (!targetUsed[j] && guess[i] == targetWord[j]) {
                    yellow.push_back(guess[i]);
                    result[i] = 'Y';
                    targetUsed[j] = true;
                    found = true;
                    break;
                }
            }
            if (!found) {
                gray.push_back(guess[i]);
                result[i] = 'X';
            }
        }
    }
    return result;
}

void printKeyboard(const vector<char>& green, const vector<char>& yellow, const vector<char>& gray) {
    char status[26] = {0};
    for (char c : green) status[tolower(c) - 'a'] = 'G';
    for (char c : yellow) {
        int idx = tolower(c) - 'a';
        if (status[idx] != 'G') status[idx] = 'Y';
    }
    for (char c : gray) {
        int idx = tolower(c) - 'a';
        if (status[idx] == 0) status[idx] = 'X';
    }

    const char* RESET = "\033[0m";
    const char* GREEN = "\033[32;1m";
    const char* YELLOW = "\033[33;1m";
    const char* GRAY = "\033[90m";

    const char* rows[] = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
    cout << "\nKeyboard:\n";
    for (int r = 0; r < 3; ++r) {
        for (size_t i = 0; i < strlen(rows[r]); ++i) {
            char ch = rows[r][i];
            int idx = ch - 'A';
            const char* color = RESET;
            if (status[idx] == 'G') color = GREEN;
            else if (status[idx] == 'Y') color = YELLOW;
            else if (status[idx] == 'X') color = GRAY;
            cout << color << ch << RESET << " ";
        }
        cout << "\n";
    }
    cout << "  (Green=correct position, Yellow=wrong position, Gray=not in word)\n" << endl;
}
