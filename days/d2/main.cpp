#include <set>     // std::set
#include <vector>  // std::vector

#include "lib/fileinput/fileinput.h"

enum class Move { rock, paper, scissor, invalid };

struct Round {
    Move opponent;
    Move player;
};

Move charToMove(char c) {
    switch (c) {
        case 'A':
        case 'X':
            return Move::rock;
            break;
        case 'B':
        case 'Y':
            return Move::paper;
            break;
        case 'C':
        case 'Z':
            return Move::scissor;
            break;
    }

    return Move::invalid;
}

Move charToMove2(char c, Move o) {
    if (c == 'Y') {  // Draw
        return o;
    } else if (c == 'X') {  // Lose round
        switch (o) {
            case Move::rock:
                return Move::scissor;
                break;
            case Move::paper:
                return Move::rock;
                break;
            case Move::scissor:
                return Move::paper;
                break;

            default:
                return Move::invalid;
                break;
        }
    } else {  // Assume c==Z, win round
        switch (o) {
            case Move::rock:
                return Move::paper;
                break;
            case Move::paper:
                return Move::scissor;
                break;
            case Move::scissor:
                return Move::rock;
                break;

            default:
                return Move::invalid;
                break;
        }
    }

    return Move::invalid;
}

uint playerPointInRound(Round r) {
    uint score = 0;
    if (r.opponent == r.player) {  // Draw
        score = 3;
    } else if ((r.player == Move::rock && r.opponent == Move::scissor) ||
               (r.player == Move::scissor && r.opponent == Move::paper) ||
               (r.player == Move::paper && r.opponent == Move::rock)) {  // Win round
        score = 6;
    } else {  // Lose round
        score = 0;
    }

    // Points based on player move
    switch (r.player) {
        case Move::rock:
            score += 1;
            break;
        case Move::paper:
            score += 2;
            break;
        case Move::scissor:
            score += 3;
            break;
        default:
            break;
    }
    return score;
}

int main(int argc, char* argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    uint sum = 0;
    for (std::string s : data) {
        Round r;
        r.opponent = charToMove(s.at(0));
        r.player = charToMove(s.at(2));

        sum += playerPointInRound(r);
    }
    std::cout << "Part 1 answer: " << sum << std::endl;

    sum = 0;
    for (std::string s : data) {
        Round r;
        r.opponent = charToMove(s.at(0));
        r.player = charToMove2(s.at(2), r.opponent);

        sum += playerPointInRound(r);
    }
    std::cout << "Part 2 answer: " << sum << std::endl;

    return 0;
}