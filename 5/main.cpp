#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

bool is_invalid(vector<int> list, unordered_map<int, vector<int>> ordering) {
    bool invalid = false;

    for (int j = 0; j < list.size(); j++) {
      int val = list[j];
      vector<int> vals = ordering[val];
      for (int k = 0; k < j; k++) {
        for (int _i = 0; _i < vals.size(); _i++) {
          if (list[k] == vals[_i]) {
            // means it is invalid
            // INVALID LINE!
            invalid = true;
            break;
          }
        }
        if (invalid)
          break;
      }
    }

    return invalid;
}

auto main(int argc, char *argv[]) -> int {

    ifstream file;
    file.open(argv[1]);

    if(!file.is_open()) {
        exit(1);
    }

    unordered_map<int, vector<int>> ordering;

    string line;

    while(getline(file, line)) {
        std::stringstream i(line);
        char garbo;
        int one;
        int two;

        i >> one >> garbo >> two;
        ordering[one].push_back(two);

        if(line.empty()) { //the actual orderings
            break;
        }
    }

    vector<vector<int>> page_numbers;

    while(getline(file,line)) {
        stringstream i(line);
        string nums;
        vector<int> page_number;

        while(getline(i, nums, ','))  {
            int num = stoi(nums);
            page_number.push_back(num);
        }
        page_numbers.push_back(page_number);
    }

    int total = 0;

    vector<vector<int>> to_fix;

    for(int i = 0; i < page_numbers.size(); i++) {
        bool invalid = false;
        for(int j = 0; j < page_numbers[i].size(); j++) {
            int val = page_numbers[i][j];
            vector<int> vals = ordering[val];
            for(int k = 0; k < j; k++) {
                for(int _i = 0; _i < vals.size();_i++) {
                    if(page_numbers[i][k] == vals[_i]) {
                        //means it is invalid
                        //INVALID LINE!
                        invalid = true;
                        to_fix.push_back(page_numbers[i]);
                        break;
                    }
                }
                if(invalid) break;
            }
            if(invalid) break;
        }
        if(!invalid) {
            int middle = ceil(page_numbers[i].size() / 2);
            total += page_numbers[i][middle];
        }
    }

    cout << to_fix.size() << endl;

    for(int i = 0; i < to_fix.size(); i++) {
        for(int j = 0; j < to_fix[i].size(); j++) {
            bool invalid = is_invalid(to_fix[i], ordering);
            if(!invalid) break;
            int k = 0;
            vector<int> nums = ordering[to_fix[i][j]];
            bool fixed = false;
            while(k < j) {
              for (int num : nums) {
                if (num == to_fix[i][k]) {
                  // needs to go in front of target(j);
                  to_fix[i].insert(to_fix[i].begin() + j + 1, num);
                  to_fix[i].erase(to_fix[i].begin() + k);
                  fixed = true;
                  break;
                }
              }
              if(fixed) {
                  j--;
                  break;
              }
              k++;
            }
        }
    }

    cout << to_fix.size() << endl;

    total = 0;

    for (int i = 0; i < to_fix.size(); i++) {
      for (int j = 0; j < to_fix[i].size(); j++) {
        cout << to_fix[i][j] << " ";
      }
      cout << endl;
      int middle = ceil(to_fix[i].size() / 2);
      total += to_fix[i][middle];
    }

    //
    // 32 | 42
    //
    //
    cout << total << endl;
    return 0;
}
