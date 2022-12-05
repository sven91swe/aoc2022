#include <algorithm>  // std::sort
#include <cassert>
#include <regex>
#include <stack>
#include <vector>  // std::vector
#define assertm(exp, msg) assert(((void)msg, exp))

#include "lib/fileinput/fileinput.h"

void splitInstructions(std::vector<std::string> const& input, std::vector<std::string>& cargo,
                       std::vector<std::string>& instructions) {
    bool empty_line_found = false;
    for (auto s : input) {
        if (s == "") {
            empty_line_found = true;
        } else {
            if (!empty_line_found) {
                cargo.emplace_back(s);
            } else {
                instructions.emplace_back(s);
            }
        }
    }
    cargo.pop_back();
}

std::vector<std::stack<std::string>> constructCargo(std::vector<std::string>& cargo_input) {
    std::vector<std::stack<std::string>> cargo, temp_cargo;

    int number_of_stacks = (cargo_input.at(0).size() + 1) / 4;

    for (int i = 0; i < number_of_stacks; i++) {
        cargo.emplace_back();
        temp_cargo.emplace_back();
    }

    for (auto s : cargo_input) {
        for (int i = 0; i < number_of_stacks; i++) {
            std::string t = s.substr(i * 4 + 1, 1);
            if (t != " ") {
                temp_cargo.at(i).emplace(t);
            }
        }
    }

    for (int i = 0; i < number_of_stacks; i++) {
        while (!temp_cargo.at(i).empty()) {
            cargo.at(i).emplace(temp_cargo.at(i).top());
            temp_cargo.at(i).pop();
        }
    }

    return cargo;
}

void moveCargo1(std::vector<std::stack<std::string>>& cargo, int number, int from_index,
                int to_index) {
    std::stack<std::string>& from = cargo.at(from_index - 1);
    std::stack<std::string>& to = cargo.at(to_index - 1);

    for (int i = 0; i < number; i++) {
        to.emplace(from.top());
        from.pop();
    }
}

void moveCargo2(std::vector<std::stack<std::string>>& cargo, int number, int from_index,
                int to_index) {
    std::stack<std::string>& from = cargo.at(from_index - 1);
    std::stack<std::string>& to = cargo.at(to_index - 1);

    std::stack<std::string> temp{};

    for (int i = 0; i < number; i++) {
        temp.emplace(from.top());
        from.pop();
    }
    while (!temp.empty()) {
        to.emplace(temp.top());
        temp.pop();
    }
}

int main(int argc, char* argv[]) {
    std::string fileName = findFileLocation(argc, argv, "input.txt");
    std::vector<std::string> data = readFileStrings(fileName);

    std::vector<std::string> cargo_data, instructions;
    splitInstructions(data, cargo_data, instructions);

    std::vector<std::stack<std::string>> cargo1 = constructCargo(cargo_data);
    std::vector<std::stack<std::string>> cargo2 = constructCargo(cargo_data);

    std::regex e(R"(\D*(\d+)\D*(\d+)\D*(\d+))");
    std::smatch string_matches;

    for (std::string s : instructions) {
        assertm(std::regex_match(s, string_matches, e), "input didn't match pattern");

        int move_number = stoi(string_matches[1]);
        int move_from = stoi(string_matches[2]);
        int move_to = stoi(string_matches[3]);

        moveCargo1(cargo1, move_number, move_from, move_to);
        moveCargo2(cargo2, move_number, move_from, move_to);
    }

    std::string answer1;
    for (auto s : cargo1) {
        answer1 += s.top();
    }

    std::string answer2;
    for (auto s : cargo2) {
        answer2 += s.top();
    }

    std::cout << "Part 1 answer: " << answer1 << std::endl;
    std::cout << "Part 2 answer: " << answer2 << std::endl;

    return 0;
}