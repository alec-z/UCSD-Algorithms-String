#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
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

void test_solution() {
  string text = "GAGAGAGA$";
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
}

int main() {
  //test_solution();
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
