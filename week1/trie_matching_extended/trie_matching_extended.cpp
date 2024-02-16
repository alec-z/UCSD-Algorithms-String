#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;

trie build_trie(const vector<string> & patterns) {
  trie t;
  t.push_back(Node());
  for (int i = 0; i < patterns.size(); i++) {
    int pointer = 0;
    for (size_t j = 0; j < patterns[i].size(); j++) {
	  char c = patterns[i][j];
      int ci = letterToIndex(c);
	  int next_pointer = t[pointer].next[ci];
      if (next_pointer != NA) pointer = next_pointer;
      else {
        t.push_back(Node());
        next_pointer = t.size() - 1;
        t[pointer].next[ci] = next_pointer;;
        pointer = next_pointer;
      }
	  if (j == patterns[i].size() - 1) {
		t[pointer].patternEnd = true;
	  }
    }
  }
  // write your code here
  return t;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	// write your code here
	trie t = build_trie(patterns);
	for (int i = 0; i < text.size(); i++) {
		int pointer = 0;
		int j = i;
		while (j < text.size() && pointer != -1) {
			pointer = t[pointer].next[letterToIndex(text[j])];
			if (pointer != -1 && t[pointer].patternEnd) {
				result.push_back(i);
				break;
			}
			j++;
		}
	}

	return result;
}



int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve(t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
