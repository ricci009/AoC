#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <istream>
#include <set>
#include <stdio.h>
#include <string>
#include <utility>
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

  // the O could create a loop that does not include itself.
  // so if it reaches the same 4 # or O then it means that there is a loop and
  // it should return true.
  //
  // if any of them have been visited again is it not a loop?
  // work on this, kind of curious about this.

  deque<pair<int, int>> boxes;

  // check if it connects... if it exits no loop.
  int row_end = map.size();
  int col_end = map[0].size();
  int distance_traveled = 0;

  pair<int, int> og_pos = coords;

  char sign = map[coords.first][coords.second];

  if (sign == '^') {
    if (map[coords.first - 1][coords.second] == '#')
      return false;
    if (coords.first == 0)
      return false;
    map[coords.first - 1][coords.second] = 'O';
    boxes.push_back({coords.first - 1, coords.second});
    map[coords.first][coords.second] = '>';
  } else if (sign == '>') {
    if (map[coords.first][coords.second + 1] == '#')
      return false;
    if (col_end == coords.second + 1)
      return false;
    map[coords.first][coords.second + 1] = 'O';
    boxes.push_back({coords.first, coords.second + 1});
    map[coords.first][coords.second] = 'v';
  } else if (sign == 'v') {
    if (map[coords.first + 1][coords.second] == '#')
      return false;
    if (row_end == coords.first + 1)
      return false;
    map[coords.first + 1][coords.second] = 'O';
    boxes.push_back({coords.first + 1, coords.second});
    map[coords.first][coords.second] = '<';
  } else if (sign == '<') {
    if (map[coords.first][coords.second - 1] == '#')
      return false;
    if (coords.second == 0)
      return false;
    map[coords.first][coords.second - 1] = 'O';
    boxes.push_back({coords.first, coords.second - 1});
    map[coords.first][coords.second] = '^';
  }

  // need to keep track of corners now.
  // so if it does a full rotation and does not reach the sign then we have
  // something on our hands.

  while (coords.first != (row_end - 1) && coords.second != (col_end - 1) &&
         coords.first > 0 && coords.second > 0) {

    if (map[coords.first][coords.second] == '^') {

      if (map[coords.first - 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
        map[--coords.first][coords.second] = '^';
      } else {
        if (boxes.size() == 4) {

          if (find(boxes.begin(), boxes.end(),
                   make_pair(coords.first - 1, coords.second)) == boxes.end()) {
            // does not exist
            boxes.pop_front();
            boxes.push_back({coords.first - 1, coords.second});
          } else {
            return true;
          }

        } else {
          boxes.push_back({coords.first - 1, coords.second});
        }
        map[coords.first][coords.second] = '>';
      }
    } else if (map[coords.first][coords.second] == '<') {

      if (map[coords.first][coords.second - 1] == '.') {
        map[coords.first][coords.second] = '.';
        map[coords.first][--coords.second] = '<';
      } else {
        if (boxes.size() == 4) {

          if (find(boxes.begin(), boxes.end(),
                   make_pair(coords.first, coords.second - 1)) == boxes.end()) {
            // does not exist
            boxes.pop_front();
            boxes.push_back({coords.first, coords.second - 1});
          } else {
            return true;
          }

        } else {
          boxes.push_back({coords.first, coords.second - 1});
        }
        map[coords.first][coords.second] = '^'; // rotate 90 degrees
      }
    } else if (map[coords.first][coords.second] == '>') {
      if (map[coords.first][coords.second + 1] == '.') {
        map[coords.first][coords.second] = '.';
        map[coords.first][++coords.second] = '>';
      } else {
        if (boxes.size() == 4) {

          if (find(boxes.begin(), boxes.end(),
                   make_pair(coords.first, coords.second + 1)) == boxes.end()) {
            // does not exist
            boxes.pop_front();
            boxes.push_back({coords.first, coords.second + 1});
          } else {
            return true;
          }

        } else {
          boxes.push_back({coords.first, coords.second + 1});
        }
        map[coords.first][coords.second] = 'v';
      }
    } else if (map[coords.first][coords.second] == 'v') {

      if (map[coords.first + 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
        map[++coords.first][coords.second] = 'v';
      } else {
        if (boxes.size() == 4) {

          if (find(boxes.begin(), boxes.end(),
                   make_pair(coords.first + 1, coords.second)) == boxes.end()) {
            // does not exist
            boxes.pop_front();
            boxes.push_back({coords.first + 1, coords.second});
          } else {
            return true;
          }

        } else {
          boxes.push_back({coords.first + 1, coords.second});
        }
        map[coords.first][coords.second] = '<';
      }
    }

    print_map(map);
  }

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
  char direction = map[coords.first][coords.second];

  set<pair<pair<int, int>, char>> checked;

  int iterations = 0;

  while (coords.first != row_end - 1 || coords.second != col_end - 1 ||
         coords.first != 0 || coords.second != 0) {

    if (checked.find({coords, direction}) == checked.end()) {
      if (check_loop(map, coords)) {
        blockers++;
      }
      checked.insert({coords, direction});
    }

    // if (check_loop(map, coords))
    //   blockers++;

    if (map[coords.first][coords.second] == '^') {

      if (map[coords.first - 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
        coords.first--;
        map[coords.first][coords.second] = '^';
      } else {
        map[coords.first][coords.second] = '>';
      }
    } else if (map[coords.first][coords.second] == '<') {

      if (map[coords.first][coords.second - 1] == '.') {
        map[coords.first][coords.second] = '.';
        coords.second--;
        map[coords.first][coords.second] = '<';
      } else {
        map[coords.first][coords.second] = '^'; // rotate 90 degrees
      }
    } else if (map[coords.first][coords.second] == '>') {

      if (map[coords.first][coords.second + 1] == '.') {
        map[coords.first][coords.second] = '.';
        coords.second++;
        map[coords.first][coords.second] = '>';
      } else {
        map[coords.first][coords.second] = 'v';
      }
    } else if (map[coords.first][coords.second] == 'v') {

      if (map[coords.first + 1][coords.second] == '.') {
        map[coords.first][coords.second] = '.';
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

    direction = map[coords.first][coords.second];
    iterations++;
  }

  cout << "BLOCKERS: " << blockers << "\n";
  cout << "ITERATIONS " << iterations << "\n";
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
