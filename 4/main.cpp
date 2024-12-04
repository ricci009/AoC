#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool search(int row, int col) {
  int count = 0;

  // forward
  //
  // backward
  //
  // diagonal
  // can have multiple diagonals
  //
  // in total about

  // xxx
  // xxx
  // xxx

  return false;
}

int main(int argc, char *argv[]) {

  ifstream f;
  f.open(argv[1]);

  if (!f.is_open()) {
    assert(false);
  }

  int count = 0;
  string line;
  vector<vector<char>> wordsearch;

  while (getline(f, line)) {
    vector<char> row;
    for (char c : line) {
      row.push_back(c);
    }
    wordsearch.push_back(row);
  }

  for (int row = 0; row < wordsearch.size(); row++) {
    for (int col = 0; col < wordsearch[row].size(); col++) {
      if (wordsearch[row][col] == 'W') {
        search(row, col);
      }
    }
  }

  cout << count << "\n";
  return 0;
}
