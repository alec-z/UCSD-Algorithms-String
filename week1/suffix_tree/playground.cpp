#include <string>
#include <iostream>
using namespace std;

int main() {
    string a = "a";
    string b = "ab";
    cout << (a < b) << endl;
    string c = "$a";
    cout << (c < a) << endl;
}