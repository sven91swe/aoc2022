#include <algorithm>  // std::sort
#include <vector>     // std::vector

#include "lib/fileinput/fileinput.h"

int main(int argc, char *argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    std::vector<uint> elf_calories;

    int currentC = 0;
    for (std::string s : data) {
        if (s == "") {  // Empty line between elfs
            elf_calories.emplace_back(currentC);
            currentC = 0;
        } else {
            currentC += stoi(s);
        }
    }

    std::sort(elf_calories.begin(), elf_calories.end());
    std::reverse(elf_calories.begin(), elf_calories.end());

    std::cout << "Part 1 answer: " << elf_calories.at(0) << std::endl;

    std::cout << "Part 2 answer: " << elf_calories.at(0) + elf_calories.at(1) + elf_calories.at(2)
              << std::endl;

    return 0;
}