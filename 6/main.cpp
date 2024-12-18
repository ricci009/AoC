#include <fstream>
#include <istream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void traversal(vector<vector<char>> &map, pair<int, int> &coords) {
  int row_end = map.size();
  int col_end = map[0].size();
  int distance_traveled = 0;
  while (coords.first != row_end || coords.second != col_end) {
    if (map[coords.first][coords.second] == '^') {
      while (map[coords.first++][coords.second] == '.') {
        coords.first = coords.first++;
        distance_traveled++;
      }
    } else if (map[coords.first][coords.second] == '<') {
      while (map[coords.first][coords.second--] == '.') {
        coords.second = coords.second--;
        distance_traveled++;
      }
    } else if (map[coords.first][coords.second] == '>') {
      while (map[coords.first][coords.second++] == '.') {
        coords.second = coords.second++;
        distance_traveled++;
      }
    } else {
      while (map[coords.first--][coords.second] == '.') {
        coords.first = coords.first--;
        distance_traveled++;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  ifstream f;
  f.open(argv[1]);

  string line;

  vector<vector<char>> map;

  pair<int, int> coords;
  int row = 0;

  while (getline(f, line)) {
    vector<char> line;
    int col = 0;

    for (char c : line) {
      if (c == 'v')
        coords = {col, row};
      line.push_back(c);
      col++;
    }
    row++;
    map.push_back(line);
  }
}
