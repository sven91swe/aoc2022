#include <algorithm>  // std::sort
#include <cassert>
#include <regex>
#include <stack>
#include <vector>  // std::vector
#define assertm(exp, msg) assert(((void)msg, exp))

#include "lib/fileinput/fileinput.h"

struct range {
    int lower;
    int upper;
};

bool containedInRange(range wider, range narrow) {
    return wider.lower <= narrow.lower && wider.upper >= narrow.upper;
}

bool overlap(range r1, range r2) {
    for (int i = r1.lower; i <= r1.upper; i++) {
        if (i >= r2.lower && i <= r2.upper) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    std::regex e(R"((\d+)-(\d+),(\d+)-(\d+))");
    std::smatch string_matches;

    uint counter_contained = 0;
    uint counter_overlap = 0;

    for (std::string s : data) {
        assertm(std::regex_match(s, string_matches, e), "input didn't match pattern");

        range r1;
        range r2;

        r1.lower = stoi(string_matches[1]);
        r1.upper = stoi(string_matches[2]);
        r2.lower = stoi(string_matches[3]);
        r2.upper = stoi(string_matches[4]);

        if (containedInRange(r1, r2) || containedInRange(r2, r1)) {
            counter_contained++;
        }

        if (overlap(r1, r2)) {
            counter_overlap++;
        }
    }

    std::cout << "Part 1 answer: " << counter_contained << std::endl;
    std::cout << "Part 2 answer: " << counter_overlap << std::endl;

    return 0;
}