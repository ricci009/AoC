#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>

int main() {
    std::unordered_map<int, int> map;
    std::vector<int> list_b;

    std::ifstream file;
    file.open("input.txt");

    if(!file.is_open()) {
        assert(false);
    }

    std::string line;
    int a;
    int b;

    while(getline(file, line)) {
        std::stringstream i(line);

        i >> a >> b;
        map[a] = 0;
        list_b.push_back(b);
    }

    for(int i = 0; i < list_b.size(); i++) {
        if(map.find(list_b[i]) != map.end()) {
            map[list_b[i]]++;
        }
    }

    int total = 0;

    for(auto it = map.begin(); it != map.end(); it++) {
        total += (it->second * it->first);
    }

    std::cout << total << "\n";

    return total;

}
