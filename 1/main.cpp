#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream input;
    input.open("input.txt");

    if(!input.is_open()) {
       assert(false);
    }

    int total = 0;

    std::string line;

    int a;
    int b;

    std::vector<int> list_a;
    std::vector<int> list_b;

    while(getline(input, line)) {
        std::stringstream linestream(line);

        linestream >> a >> b;

       list_a.push_back(a);
       list_b.push_back(b);
    }

    std::sort(list_a.begin(), list_a.end());
    std::sort(list_b.begin(), list_b.end());

    for(int i = 0; i < list_a.size(); i++) {
       total += abs(list_b[i] - list_a[i]);
    }

    std::cout << total << "\n";

    return total;
}
