#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::pair;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

typedef map<string, int> Edge;
typedef vector<Edge> Trie;

vector<string> ComputeSuffixTreeEdges(const string& text) {
  Trie t;
  t.push_back(Edge());
  vector<string> results;

  
  // Implement this function yourself
  for (int i = text.size() - 1; i >= 0; i--) {
      int pointer = 0;
      string suffix = text.substr(i, text.size() - i);
      while (!suffix.empty()) {
        auto p = t[pointer].lower_bound(suffix);
        auto left_p = p;
        auto p_e = p;
        int comm_prefix_l = 0;
        if (p != t[pointer].begin()) {
          left_p--;
          const string & edge_string = (*left_p).first;
           auto mis_p = std::mismatch(edge_string.begin(), edge_string.end(), suffix.begin());
           comm_prefix_l = (mis_p.first - edge_string.begin());
           if (comm_prefix_l > 0) {
            p_e = left_p;
           }
        }

        
        int comm_prefix_l2 = 0;
        if (p != t[pointer].end()) {
          const string & edge_string = (*p).first;
          auto mis_p = std::mismatch(edge_string.begin(), edge_string.end(), suffix.begin());
          comm_prefix_l2 = (mis_p.first - edge_string.begin());
          if (comm_prefix_l2 > comm_prefix_l) {
            comm_prefix_l = comm_prefix_l2;
            p_e = p;
          }
        }
        

        if (comm_prefix_l == 0) {
          t.push_back(Edge());
          t[pointer][suffix] = t.size() - 1;
          suffix = "";
        } else {
          
          string edge_string = (*p_e).first;
          int next_pointer = (*p_e).second;
          // remove old edge, add new edge
          if (edge_string.size() - comm_prefix_l > 0) {
            t[pointer].erase(edge_string);
            t[pointer].insert({edge_string.substr(0, comm_prefix_l), next_pointer});
            pointer = next_pointer;
            t.push_back(Edge());
            t[pointer].insert({edge_string.substr(comm_prefix_l, edge_string.size() - comm_prefix_l), t.size() - 1});
          } else {
            pointer = next_pointer;
          }
          
          suffix = suffix.substr(comm_prefix_l, suffix.size() - comm_prefix_l);
          
        }
      }
  }

  for (int i = 0; i < t.size(); i++) {
    for (auto j: t[i])
      results.push_back(j.first);
  }
  return results;
}

void test_solution() {
  string text = "ATTGTCACAACTGCGAGCGGCTAAATTTGGTAATTCTGCCGGTAAACGAAAACAACGACCTCGGGCTCAGCCAGGAGAGCGTTGGAGGCTCGACAATTAA$";
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
}



int main() {
  test_solution();
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
