#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using std::cin;
using std::string;
using std::vector;

vector<int> counting_order(vector<int>& input_array, std::function<int(int)> to_class, int class_len) {
  vector<int> res(input_array.size(), -1);
  vector<int> count(class_len, 0);
  for (int element: input_array) {
    int class_id = to_class(element);
    count[class_id]++;
  }
  for (int i = 1; i < class_len; i++) {
    count[i] += count[i - 1];
  }
  int i = input_array.size() - 1;
  for (int i = input_array.size() - 1; i >= 0; i--) {
    int element = input_array[i];
    int c = to_class(element);
    res[--count[c]] = element;
  }
  return res;
}

vector<int> get_to_class_array(vector<int> & order, std::function<bool(int, int)>  is_element_equal) {
  vector<int> to_class_array(order.size(), 0);
  int class_id = 0;
  to_class_array[order[0]] = class_id;
  for (int i = 1; i < order.size(); i++) {
    int element = order[i];
    int previous_element = order[i - 1];
    if (!is_element_equal(element, previous_element)) {
      class_id ++;
    }
    to_class_array[element] = class_id;
  }
  return to_class_array;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  int n = text.size();
  // Implement this function yourself
  vector<int> char_array(n, 0);
  for (int i = 0; i < n; i++) {
    char_array[i] = text[i];
  }
  vector<int> partial_suffix_l_1(n, 0);
  for (int i = 0; i < n; i++) partial_suffix_l_1[i] = i;
  auto first_to_class = [&char_array](int i) {
    switch (char_array[i]) {
      case '$': return 0; break;
      case 'A': return 1; break;
      case 'C': return 2; break;
      case 'G': return 3; break;
      case 'T': return 4; break;
      default: return -1; break;
    }
  };
  auto order = counting_order(partial_suffix_l_1, first_to_class, 5);
  auto to_class_array = get_to_class_array(order, [&char_array](int i, int j) { return char_array[i] == char_array[j];} );
  int l = 1;
  while (l < text.size()) {
    for (int i = 0; i < n; i++) order[i] = (order[i] - l + n) % n; 
    order = counting_order(order, [&to_class_array](int e) { return to_class_array[e];}, to_class_array.size());
    to_class_array = get_to_class_array(order, [&to_class_array, l, n](int i, int j) { return to_class_array[i] == to_class_array[j] && to_class_array[(i + l) % n] == to_class_array[(j + l) % n] ;} );
    l = 2 * l;
  }
  
  return order;
}

int letter_to_class(char c) {
  switch (c) {
      case '$': return 0; break;
      case 'A': return 1; break;
      case 'C': return 2; break;
      case 'G': return 3; break;
      case 'T': return 4; break;
      default: return -1; break;
    }
}

vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
  vector<int> result;
  int n = text.size();
  vector<char> last_column(n);
  vector<int> count(5, 0);
  for (int i = 0; i < n; i++) {
    last_column[i] = text[(suffix_array[i] + n - 1) % n];
  }
  int count_s[n+1][5];
  for (int i = 0; i < 5; i++) count_s[0][i] = 0;
  for (int i = 1; i < n + 1; i++) {
    for (int j = 0; j < 5; j++) count_s[i][j] = count_s[i - 1][j];
    count_s[i][letter_to_class(last_column[i - 1])]++;
  }
  vector<int> first_occurrence(5, 0);
  for (int i = 1; i < first_occurrence.size(); i++) {
    first_occurrence[i] = first_occurrence[i - 1] + count_s[n][i - 1];
  }
  int top = 0, bottom = n - 1, i = pattern.size() - 1;
  while (top <= bottom && i >= 0) {
    int c = letter_to_class(pattern[i]);
    if (c == -1) return result;

    top = first_occurrence[c] + count_s[top][c];
    bottom = first_occurrence[c] + count_s[bottom + 1][c] - 1;
    i--;
  }
  for (int i = top; i <= bottom; i++)
    result.push_back(suffix_array[i]);

  return result;
}

void test_solution() {
  string text = "TAAAA";
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count = 3;
  vector<string> patterns = {"AAA", "G", "C"};
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    string pattern = patterns[pattern_index];
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }


}

int main() {
  //test_solution();
  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
    for (int j = 0; j < occurrences.size(); ++j) {
      occurs[occurrences[j]] = true;
    }
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}
