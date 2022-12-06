#include <set>     // std::set
#include <vector>  // std::vector

#include "lib/fileinput/fileinput.h"

uint getCharValue(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int main(int argc, char* argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    uint sum = 0;

    for (std::string s : data) {
        std::string first_half = s.substr(0, s.length() / 2);
        std::string second_half = s.substr(s.length() / 2);

        std::set<char> set_of_matches;
        for (char& c : first_half) {
            if (second_half.find(c) != std::string::npos) {
                set_of_matches.insert(c);
            }
        }

        std::set<char>::iterator it;
        for (it = set_of_matches.begin(); it != set_of_matches.end(); it++) {
            sum += getCharValue(*it);
        }
    }

    std::cout << "Part 1 answer: " << sum << std::endl;

    sum = 0;
    for (uint i = 0; i < data.size(); i = i + 3) {
        std::string s1 = data.at(i);
        std::string s2 = data.at(i + 1);
        std::string s3 = data.at(i + 2);

        std::set<char> set_of_matches;
        for (char& c : s1) {
            if (s2.find(c) != std::string::npos && s3.find(c) != std::string::npos) {
                set_of_matches.insert(c);
            }
        }
        std::set<char>::iterator it;
        for (it = set_of_matches.begin(); it != set_of_matches.end(); it++) {
            sum += getCharValue(*it);
        }
    }

    std::cout << "Part 2 answer: " << sum << std::endl;

    return 0;
}