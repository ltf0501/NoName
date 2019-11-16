#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
  freopen("boolean.in", "r", stdin);
  freopen("boolean.out", "w", stdout);
#endif
  string str;
  cin >> str;
  for (char &c : str) c = c == '|' ? '\n' : c;
  stringstream ss(str);
  string tmp;
  map<char, int> mp;
  while (ss >> tmp) {
    if (tmp.size() == 1) {
      mp[tmp[0]] |= 1;
    } else {
      mp[tmp[1]] |= 2;
    }
  }
  int64_t ans = 1LL << int(mp.size());
  bool yay = false;
  for (auto p : mp) yay |= p.second == 3;
  cout << (yay ? ans : (ans - 1)) << endl;
}
