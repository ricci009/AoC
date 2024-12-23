#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  fstream f;
  f.open(argv[1]);

  string line;

  vector<string> lines;

  unordered_map<unsigned long long, vector<unsigned long long>> associated_vals;

  while (getline(f, line)) {
    lines.push_back(line);
    unsigned long long product;
    string curr_int;

    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ':') {
        product = stoull(curr_int);
        associated_vals[product];
        curr_int.clear();
        i++;
      }
      if (line[i] == ' ') {
        associated_vals[product].push_back(stoull(curr_int));
        curr_int.clear();
      } else {
        curr_int.push_back(line[i]);
      }
    }
  }
}
