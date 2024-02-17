#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";
  vector<string> res;
  // write your code here
  for (int i = 0; i < text.size(); i++) {
    res.push_back(text.substr(i, text.size() - i) + text.substr(0, i));    
  }
  sort(res.begin(), res.end());
  for (int i = 0; i < text.size(); i++) {
    result += res[i][text.size() - 1];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}