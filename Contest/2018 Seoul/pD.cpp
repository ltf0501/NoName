#include <iostream>
using namespace std;
int main() {
  int n;
  string s;
  cin >> n;
  while (n--) {
    cin >> s;
    if (s.back() == 'a')
      s += "s";
    else if (s.back() == 'i' || s.back() == 'y') {
      s.back() = 'i';
      s += "os";
    } else if (s.back() == 'l')
      s += "es";
    else if (s.back() == 'o')
      s += "s";
    else if (s.back() == 'r')
      s += "es";
    else if (s.back() == 't' || s.back() == 'w')
      s += "as";
    else if (s.back() == 'u')
      s += "s";
    else if (s.back() == 'v')
      s += "es";
    else if (s.back() == 'e') {
      if (s.size() > 1 && s[s.size() - 2] == 'n') {
        s[s.size() - 2] = 'a';
        s.back() = 'n';
        s += "es";
      } else
        s += "us";
    } else if (s.back() == 'n') {
      s.back() = 'a';
      s += "nes";
    } else
      s += "us";
    cout << s << endl;
  }
}
