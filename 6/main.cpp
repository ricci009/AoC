#include <fstream>
#include <istream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

void find_distance(vector<vector<char>> &map) {
  int distance = 0;
  for(int i = 0; i < map.size(); i++){
    for(int j = 0; j < map.size(); j++) {
      if(map[i][j] == 'X') {
        distance++;
      }
    }
  }
  std::cout << distance;
}

void traversal(vector<vector<char>> &map, pair<int, int> &coords) {
  int row_end = map.size();
  int col_end = map[0].size();
  int distance_traveled = 0;

  while (coords.first != row_end - 1 || coords.second != col_end - 1 || coords.first != 0 || coords.second != 0) {
    distance_traveled++;
    if (map[coords.first][coords.second] == '^') {
      if (map[coords.first - 1][coords.second] == '.' || map[coords.first - 1][coords.second] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.first--;
        map[coords.first][coords.second] = '^';
      }
      else {
        map[coords.first][coords.second] = '>';
      }
    } else if (map[coords.first][coords.second] == '<') {
      if (map[coords.first][coords.second - 1] == '.' || map[coords.first][coords.second - 1] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.second--;
        map[coords.first][coords.second] = '<';
      }
      else {
         map[coords.first][coords.second] = '^';       //rotate 90 degrees
      }
    } else if (map[coords.first][coords.second] == '>') {
      if (map[coords.first][coords.second + 1] == '.' || map[coords.first][coords.second + 1] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.second++;
        map[coords.first][coords.second] = '>';
      }
      else {
        map[coords.first][coords.second] = 'v';
      }
    } else if (map[coords.first][coords.second] == 'v') {
      if (map[coords.first + 1][coords.second] == '.' || map[coords.first + 1][coords.second] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.first++;
        map[coords.first][coords.second] = 'v';
      }
      else {
        map[coords.first][coords.second] = '<';
      }
    }


    if(coords.first == map.size() - 1) break;
    if(coords.second == map[0].size() - 1) break;
    if(coords.first == 0) break;
    if(coords.second == 0) break;

  }
  map[coords.first][coords.second] = 'X';

  find_distance(map);
}

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

  traversal(map, coords);
  return 0;
}
