#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int letterToIndex(char c) {
  switch(c) { //A, C, G, T
    case '$': return 0; break;
    case 'A': return 1; break;
    case 'C': return 2; break;
    case 'G': return 3; break;
    case 'T': return 4; break;
    default: assert(false); return -1; break;
  }
}

string InverseBWT(const string& bwt) {
  string text = "";
  int n = bwt.size();
  vector<int> l_to_f(n);
  int nums[5] = {0,0,0,0,0};
  int see_nums[5] = {0,0,0,0,0};
  for (char c: bwt) nums[letterToIndex(c)]++;
  for (int i = 0; i < n; i++) {
    char c = bwt[i];
    int ci = letterToIndex(c);
    int less_than = 0;
    for (int j = 0; j < ci; j++) less_than += nums[j];
    l_to_f[i] = less_than + see_nums[ci];
    
    

    see_nums[ci] ++; 
  }

  text = "$";
  int p = 0;
  for (int i = 0; i < bwt.size() - 1; i++) {
    text += bwt[p];
    p = l_to_f[p];
  }

  std::reverse(text.begin(), text.end());
  // write your code here

  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
