#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

string XMAS = "XMAS";

int search(int row, int col, vector<vector<char>> &wordsearch) {

  set<char> mors;
  mors.insert('M');
  mors.insert('S');

  vector<pair<int, int>> one;
  vector<pair<int, int>> two;

  bool one_true = false;
  bool two_true = false;

  //half of the x
  one.push_back({-1, 1}); //tr
  one.push_back({1, -1}); //bl

  //other half of the x
  two.push_back({-1, -1}); //tl
  two.push_back({1, 1}); //br

  int count = 0;

  set<char> cpy = mors;
  while(one.size() > 0){
    pair<int,int> increment = one.back();
    one.pop_back();
    int _row = row;
    int _col = col;

    _row = _row + increment.first;
    _col = _col + increment.second;

    if(cpy.find(wordsearch[_row][_col]) != cpy.end()) {
      cpy.erase(wordsearch[_row][_col]);
    }

    if(cpy.empty()) {
      one_true = true;
    }
  }

  if(!one_true) return 0;

  cpy = mors;
  while(two.size() > 0){
    pair<int, int> increment = two.back();
    two.pop_back();
    int _row = row;
    int _col = col;

    _row = _row + increment.first;
    _col = _col + increment.second;

    if(cpy.find(wordsearch[_row][_col]) != cpy.end()) {
      cpy.erase(wordsearch[_row][_col]);
    }

    if(cpy.empty()) {
      two_true = true;
    }

  }


  if(!two_true) {
    return 0;
  }

  return 1;
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
    if(row == 0 || row == wordsearch.size() - 1) continue;
    for (int col = 0; col < wordsearch[row].size(); col++) {
      if(col == 0 || col == wordsearch[row].size() - 1) continue;
      if (wordsearch[row][col] == 'A') {
        count += search(row, col, wordsearch);
      }
    }
  }

  cout << count << "\n";
  return 0;
}
