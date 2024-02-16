#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  t.push_back(edges());
  for (int i = 0; i < patterns.size(); i++) {
    int pointer = 0;
    for (char c: patterns[i]) {
      auto p_next_pointer = t[pointer].find(c);
      if (p_next_pointer != t[pointer].end()) pointer = (*p_next_pointer).second;
      else {
        t.push_back(edges());
        int next_pointer = t.size() - 1;
        t[pointer][c] = next_pointer;;
        pointer = next_pointer;
      }
    }
  }
  // write your code here
  return t;
}

trie test_solution() {
  vector<string> patterns {"ATAGA","ATC","GAT"};
  return build_trie(patterns);
}

int main() {
  //trie t = test_solution();
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);

  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}