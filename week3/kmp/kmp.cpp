#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  const int ps = pattern.size();
  const string all_text = pattern + "$" + text;
  vector<int> prefix_f(all_text.size(), 0);
  int border = 0;
  for (int i = 1; i < all_text.size(); i++) {
    while (border > 0 && all_text[border] != all_text[i]) {
      border = prefix_f[border - 1];
    }
    if (all_text[border] == all_text[i]) {
      border += 1;
    }
    else {
      border = 0;
    }
    prefix_f[i] = border;
    if (border == ps) {
      result.push_back(i - 2 * border);
    }
  }
  return result;
}

void test_solution() {
  string pattern = "ATA";
  string text = "ATATA";
  find_pattern(pattern, text);
}

int main() {
  //test_solution();
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
