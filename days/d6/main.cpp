#include <deque>   // std::deque
#include <vector>  // std::vector

#include "lib/fileinput/fileinput.h"

bool allUnique(std::deque<char>& in) {
    for (uint i = 0; i < in.size(); i++) {
        for (uint j = i + 1; j < in.size(); j++) {
            if (in.at(i) == in.at(j)) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::string data = readFileStrings(fileName).at(0);

    auto f = [data](uint marker_size) {
        uint current_letter = 0;
        std::deque<char> letter_buffer;
        for (char c : data) {
            current_letter++;
            letter_buffer.push_back(c);
            if (letter_buffer.size() > marker_size) {
                letter_buffer.pop_front();
            }

            if (letter_buffer.size() == marker_size) {
                if (allUnique(letter_buffer)) {
                    break;
                }
            }
        }
        return current_letter;
    };

    std::cout << "Part 1 answer: " << f(4) << std::endl;
    std::cout << "Part 2 answer: " << f(14) << std::endl;

    return 0;
}