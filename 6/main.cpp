#include <cassert>
#include <fstream>
#include <iostream>
#include <istream>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void print_map(vector<vector<char>> &map) {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      cout << map[i][j];
    }
    cout << "\n";
  }
  cout << "\n\n";
}

void find_distance(vector<vector<char>> &map) {
  int distance = 0;
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map.size(); j++) {
      if (map[i][j] == 'X') {
        distance++;
      }
    }
  }
  distance++;
  std::cout << distance;
}

// want to create a new block.
// check if there is a loop as in the block goes back up

bool check_loop(vector<vector<char>> map, pair<int, int> coords) {

  // check if it connects... if it exits no loop.
  int row_end = map.size();
  int col_end = map[0].size();
  int distance_traveled = 0;

  char sign = map[coords.first][coords.second];

  if (sign == '^') {
    if (map[coords.first - 1][coords.second] == '#')
      return false;
    if (coords.first == 0)
      return false;
    map[coords.first - 1][coords.second] = 'O';
    map[coords.first][coords.second] = '>';
  } else if (sign == '>') {
    if (map[coords.first][coords.second + 1] == '#')
      return false;
    if (col_end == coords.second + 1)
      return false;
    map[coords.first][coords.second + 1] = 'O';
    map[coords.first][coords.second] = 'v';
  } else if (sign == 'v') {
    if (map[coords.first + 1][coords.second] == '#')
      return false;
    if (row_end == coords.first + 1)
      return false;
    map[coords.first + 1][coords.second] = 'O';
    map[coords.first][coords.second] = '<';
  } else if (sign == '<') {
    if (map[coords.first][coords.second - 1] == '#')
      return false;
    if (coords.second == 0)
      return false;
    map[coords.first][coords.second - 1] = 'O';
    map[coords.first][coords.second] = '^';
  }

  // need to keep track of corners now.
  // so if it does a full rotation and does not reach the sign then we have
  // something on our hands.
  int rotations = 0;

  while (rotations < 5 && coords.first != (row_end - 1) &&
         coords.second != (col_end - 1) && coords.first > 0 &&
         coords.second > 0) {

    if (map[coords.first][coords.second] == '^') {

      if (map[coords.first - 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
        map[--coords.first][coords.second] = '^';
      } else {
        if (rotations == 4 && map[coords.first - 1][coords.second] == 'O') {
          return true;
        }
        rotations++;
        map[coords.first][coords.second] = '>';
      }
    } else if (map[coords.first][coords.second] == '<') {

      if (map[coords.first][coords.second - 1] == '.') {
        map[coords.first][coords.second] = '.';
        map[coords.first][--coords.second] = '<';
      } else {
        if (rotations == 4 && map[coords.first][coords.second - 1] == 'O') {
          return true;
        }
        rotations++;
        map[coords.first][coords.second] = '^'; // rotate 90 degrees
      }
    } else if (map[coords.first][coords.second] == '>') {
      if (map[coords.first][coords.second + 1] == '.') {
        map[coords.first][coords.second] = '.';
        map[coords.first][++coords.second] = '>';
      } else {
        if (rotations == 4 && map[coords.first][coords.second + 1] == 'O') {
          return true;
        }
        rotations++;
        map[coords.first][coords.second] = 'v';
      }
    } else if (map[coords.first][coords.second] == 'v') {

      if (map[coords.first + 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
        map[++coords.first][coords.second] = 'v';
      } else {
        if (rotations == 4 && map[coords.first + 1][coords.second] == 'O') {
          return true;
        }
        rotations++;
        map[coords.first][coords.second] = '<';
      }
    }
  }

  cout << "RETURNING FALSE\n";

  return false;
}

void traversal(vector<vector<char>> &map, pair<int, int> &coords) {
  vector<vector<char>> og_map = map;
  int row_end = map.size();
  int col_end = map[0].size();
  int distance_traveled = 0;

  int blockers = 0;

  // need to keep track of corners now.
  pair<int, int> og_pos = coords;

  set<pair<pair<int, int>, char>> checked;

  while (coords.first != row_end - 1 || coords.second != col_end - 1 ||
         coords.first != 0 || coords.second != 0) {

    if (check_loop(og_map, coords)) {
      blockers++;
    }

    if (map[coords.first][coords.second] == '^') {

      if (map[coords.first - 1][coords.second] == '.' ||
          map[coords.first - 1][coords.second] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.first--;
        map[coords.first][coords.second] = '^';
      } else {
        map[coords.first][coords.second] = '>';
      }
    } else if (map[coords.first][coords.second] == '<') {

      if (map[coords.first][coords.second - 1] == '.' ||
          map[coords.first][coords.second - 1] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.second--;
        map[coords.first][coords.second] = '<';
      } else {
        map[coords.first][coords.second] = '^'; // rotate 90 degrees
      }
    } else if (map[coords.first][coords.second] == '>') {

      if (map[coords.first][coords.second + 1] == '.' ||
          map[coords.first][coords.second + 1] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.second++;
        map[coords.first][coords.second] = '>';
      } else {
        map[coords.first][coords.second] = 'v';
      }
    } else if (map[coords.first][coords.second] == 'v') {

      if (map[coords.first + 1][coords.second] == '.' ||
          map[coords.first + 1][coords.second] == 'X') {
        map[coords.first][coords.second] = 'X';
        coords.first++;
        map[coords.first][coords.second] = 'v';
      } else {
        map[coords.first][coords.second] = '<';
      }
    }

    if (coords.first == map.size() - 1)
      break;
    if (coords.second == map[0].size() - 1)
      break;
    if (coords.first == 0)
      break;
    if (coords.second == 0)
      break;
  }

  cout << "BLOCKERS: " << blockers << "\n";
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
