#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>

auto main(int argc, char *argv[]) -> int {

    std::ifstream file;

    file.open(argv[1]);

    bool enabled = true;

    std::regex expression(R"(do\(\)|don\'t\(\)|mul\((\d{1,3}),(\d{1,3})\))"); //basically include do and dont in here.

    std::string s;

    int total = 0;

    while(getline(file, s)) {
        auto begin = s.cbegin();
        auto end = s.cend();
        std::smatch sm;


        while(std::regex_search(begin, end, sm, expression)) {
          if (sm[0] == "don't()")
            enabled = false;
          else if (sm[0] == "do()")
            enabled = true;
          else {
            if (enabled)
              total += (std::stoi(sm[1]) * std::stoi(sm[2]));
          }
          begin = sm.suffix().first;
        }
    }

    std::cout << total << "\n";

    return 0;
}
