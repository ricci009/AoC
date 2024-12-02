#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>

bool is_safe(std::vector<int> report) {
    bool increasing;

    if(report.size() >= 2) {
        if((report[0] - report[1]) > 0) {
            increasing = false;
        }
        else if((report[0] - report[1]) < 0) {
            increasing = true;
        }
        else {
            return false;
        }
    }

    for(int i = 0; i < report.size() - 1; i++) {
        int dif = report[i] - report[i + 1];

        if(abs(dif) < 1 || abs(dif) > 3) {
            return false;
        }

        if((dif < 0 && increasing) || (dif > 0 && !increasing)){
            continue;
        }
        else {
            return false;
        }
    }

    return true;

}

auto main(int argc, char *argv[]) -> int {
    if(argc < 2) {
       assert(false);
    }

    std::vector<std::vector<int>> reports;

    std::ifstream input;

    input.open(argv[1]);

    if(!input.is_open()) {
        assert(false);
    }

    std::string line;

    int val;

    while(getline(input, line)) {
        std::stringstream i(line);
        std::vector<int> level;

        while(i >> val) {
            level.push_back(val);
        }

        reports.push_back(level);
    }


    // The levels are either all increasing or all decreasing.
    // Any two adjacent levels differ by at least one and at most three.
    int total_safe = 0;

    for(auto &report: reports) {
        bool safe = false;

        int prev_diff;

        int total_diffs = 0;


        if(is_safe(report)) {
            total_safe++;
            continue;
        }

        for(int i = 0; i < report.size(); i++) {
            std::vector<int> copy_report = report;
            copy_report.erase(copy_report.begin() + i);
            if(is_safe(copy_report)) {
                safe = true;
                break;
            }
        }

        if(safe) {
            total_safe++;
            safe = false;
        }
    }

    std::cout << total_safe << "\n";

    return total_safe;
}
