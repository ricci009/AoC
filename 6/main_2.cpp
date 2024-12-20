#include <fstream>
#include <istream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

//single traversal to see if they are reached.
//
//if reached then add to reched blocks.

int main(int argc, char *argv[]) {
  ifstream f;
  f.open(argv[1]);

  string line;

  vector<vector<char>> map;

  pair<int, int> coords;
  int row = 0;

  while (getline(f, line)) {
    vector<char> v_row;
    int col = 0;

    for (char c : line) {
      if (c == '^') {
        coords = {row, col};

      }
      v_row.push_back(c);
      col++;
    }
    row++;
    map.push_back(v_row);
  }

  return 0;
}
