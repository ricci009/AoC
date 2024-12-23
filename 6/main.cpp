#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

void print_map(vector<vector<char>> &map) {
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      cout << map[i][j];
    }
    cout << "\n";
  }
  cout << "\n\n";
}

Direction get_direction(vector<vector<char>> &map, pair<int, int> &coords) {
  if (map[coords.first][coords.second] == '^') {
    return UP;
  } else if (map[coords.first][coords.second] == '>') {
    return RIGHT;
  } else if (map[coords.first][coords.second] == 'v') {
    return DOWN;
  } else if (map[coords.first][coords.second] == '<') {
    return LEFT;
  } else {
    assert(false);
  }
}

bool is_spot_empty(vector<vector<char>> &map, pair<int, int> &coords) {
  Direction dir = get_direction(map, coords);
  int x = coords.first;
  int y = coords.second;
  if (RIGHT) {
    y++;
  }
  if (LEFT) {
    y--;
  }
  if (UP) {
    x--;
  }
  if (DOWN) {
    x++;
  }

  if (map[x][y] == '.') {
    return true;
  }
  return false;
}

void turn_right(vector<vector<char>> &map, pair<int, int> &coords,
                Direction &direction) {
  switch (direction) {
  case UP:
    direction = RIGHT;
    map[coords.first][coords.second] = '>';
    break;

  case DOWN:
    direction = LEFT;
    map[coords.first][coords.second] = '<';
    break;

  case LEFT:
    direction = UP;
    map[coords.first][coords.second] = '^';
    break;

  case RIGHT:
    direction = DOWN;
    map[coords.first][coords.second] = 'v';
    break;
  }
}

bool check_boundaries(vector<vector<char>> &map, pair<int, int> &coords) {
  Direction curr_direction = get_direction(map, coords);

  if (curr_direction == RIGHT) {
    if (coords.second + 1 >= map[0].size()) {
      return false;
    } else {
      return true;
    }
  }
  if (curr_direction == LEFT) {
    if (coords.second - 1 < 0) {
      return false;
    } else {
      return true;
    }
  }
  if (curr_direction == UP) {
    if (coords.first - 1 < 0) {
      return false;
    } else {
      return true;
    }
  }
  if (curr_direction == DOWN) {
    if (coords.first + 1 >= map.size()) {
      return false;
    } else {
      return true;
    }
  }

  return false;
}

bool traverse(vector<vector<char>> &map, pair<int, int> &coords,
              Direction &direction) {
  if (direction == UP) {
    if (map[coords.first - 1][coords.second] == '.') {
      map[coords.first][coords.second] = '.';
      coords.first--;
      map[coords.first][coords.second] = '^';
    } else {
      turn_right(map, coords, direction);
      return true;
    }
  } else if (direction == DOWN) {
    if (map[coords.first + 1][coords.second] == '.') {
      map[coords.first][coords.second] = '.';
      coords.first++;
      map[coords.first][coords.second] = 'v';
    } else {
      turn_right(map, coords, direction);
      return true;
    }
  } else if (direction == RIGHT) {
    if (map[coords.first][coords.second + 1] == '.') {
      map[coords.first][coords.second] = '.';
      coords.second++;
      map[coords.first][coords.second] = '>';
    } else {
      turn_right(map, coords, direction);
      return true;
    }
  } else if (direction == LEFT) {
    if (map[coords.first][coords.second - 1] == '.') {
      map[coords.first][coords.second] = '.';
      coords.second--;
      map[coords.first][coords.second] = '<';
    } else {
      turn_right(map, coords, direction);
      return true;
    }
  }
  return false;
}

bool add_blocker(vector<vector<char>> &map, pair<int, int> &coords) {
  Direction curr_direction = get_direction(map, coords);
  if (!check_boundaries(map, coords))
    return false;
  int x = coords.first;
  int y = coords.second;

  switch (curr_direction) {
  case UP:
    x = coords.first - 1;
    break;

  case DOWN:
    x = coords.first + 1;
    break;

  case RIGHT:
    y = coords.second + 1;
    break;

  case LEFT:
    y = coords.second - 1;
    break;
  }

  map[x][y] = '#';
  return true;
}

pair<int, int> get_blocker_coords(vector<vector<char>> map,
                                  pair<int, int> coords) {
  Direction curr_direction = get_direction(map, coords);
  if (!check_boundaries(map, coords))
    return {-1, -1};
  int x = coords.first;
  int y = coords.second;

  switch (curr_direction) {
  case UP:
    x = coords.first - 1;
    break;

  case DOWN:
    x = coords.first + 1;
    break;

  case RIGHT:
    y = coords.second + 1;
    break;

  case LEFT:
    y = coords.second - 1;
    break;
  }

  return {x, y};
}

bool check_loop(vector<vector<char>> map, pair<int, int> coords) {

  set<pair<pair<int, int>, Direction>> loop_checker;

  int steps = 0;

  // if (!add_blocker(map, coords))
  //   return false;

  while (check_boundaries(map, coords)) {
    Direction curr_direction = get_direction(map, coords);
    Direction prev_dir = curr_direction;
    if (traverse(map, coords, curr_direction)) {
      if (loop_checker.find(make_pair(coords, prev_dir)) !=
          loop_checker.end()) {
        return true;
      } else {
        loop_checker.insert(make_pair(coords, prev_dir));
      }
    }
  }
  return false;
}

int traverse_map(vector<vector<char>> &map, pair<int, int> &coords) {
  int loops = 0;
  set<pair<int, int>> blockers;

  pair<int, int> start_coords = coords;

  for (int x = 0; x < map.size(); x++) {
    for (int y = 0; y < map[x].size(); y++) {
      if (start_coords.first == x && start_coords.second == y) {
        continue;
      } else {
        vector<vector<char>> copy_map = map;
        copy_map[x][y] = '#';
        if (check_loop(copy_map, start_coords)) {
          loops++;
        }
      }
    }
  }

  bool p1 = false;
  if (p1) {
    while (check_boundaries(map, coords)) {
      Direction dir = get_direction(map, coords);

      if (is_spot_empty(map, coords)) {
        pair<int, int> blocker_coords = get_blocker_coords(map, coords);
        if (blockers.find(blocker_coords) == blockers.end()) {
          // if (check_loop(map, coords, blockers)) {
          //   loops++;
          //   blockers.insert(blocker_coords);
          // }
        }
      }

      traverse(map, coords, dir);
    }
  }
  return loops;
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

  cout << traverse_map(map, coords) << "\n";

  return 0;
}
