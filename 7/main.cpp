#include <cassert>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#define ull unsigned long long

using namespace std;

bool check_product(vector<char> &curr_operators, vector<ull> &vals,
                   const ull &product) {
  ull curr_product = vals[0];

  assert(curr_operators.size() == vals.size() - 1);

  for (int i = 0; i < curr_operators.size(); i++) {
    if (curr_operators[i] == '+') {
      curr_product = curr_product + vals[i + 1];
    }
    if (curr_operators[i] == '*') {
      curr_product = curr_product * vals[i + 1];
    }
  }

  if (curr_product == product) {
    return true;
  } else {
    return false;
  }
}

bool try_possibility(ull &product, vector<ull> &vals, vector<char> curr_vals) {

  if (curr_vals.size() == vals.size() - 1) {
    return check_product(curr_vals, vals, product);
  }

  bool plus_works;
  bool mult_works;

  curr_vals.push_back('+');
  plus_works = try_possibility(product, vals, curr_vals);
  curr_vals.pop_back();

  curr_vals.push_back('*');
  mult_works = try_possibility(product, vals, curr_vals);
  curr_vals.pop_back();

  return plus_works || mult_works;
}

bool find_product(ull product, vector<ull> &vals) {
  int possible_spots = vals.size() - 1;

  vector<char> curr_vals;

  bool result = try_possibility(product, vals, curr_vals);

  return result;
}

int main(int argc, char *argv[]) {
  fstream f;
  f.open(argv[1]);

  string line;

  vector<string> lines;

  unordered_map<ull, vector<ull>> associated_vals;

  while (getline(f, line)) {
    lines.push_back(line);
    unsigned long long product;
    string curr_int;

    for (int i = 0; i < line.size(); i++) {
      if (line[i] == ':') {
        product = stoull(curr_int.c_str());
        associated_vals[product];
        curr_int.clear();
        i++;
      } else if (line[i] == ' ') {
        associated_vals[product].push_back(stoull(curr_int));
        curr_int.clear();
      } else {
        curr_int.push_back(line[i]);
        if (i + 1 == line.size())
          associated_vals[product].push_back(stoull(curr_int));
      }
    }
  }

  ull total = 0;
  for (auto it = associated_vals.begin(); it != associated_vals.end(); it++) {
    cout << "product: " << it->first << "\n";
    if (find_product(it->first, it->second)) {
      total += it->first;
    }
  }

  cout << total << "\n";
  return 0;
}
