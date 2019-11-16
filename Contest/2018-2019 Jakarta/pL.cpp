#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  int64_t k;
  cin >> k;
  string s;
  cin >> s;
  int ans = INT_MAX;
  for (int i = 60; i >= 0; i--) {
    string tmp = s;
    int cnt = 0;
    while (int(tmp.size()) > i) {
      int j;
      for (j = 1; j < int(tmp.size()); j++) {
        if (tmp[j] == '1') break;
      }
      if (j < int(tmp.size()))
        tmp.erase(j, 1);
      else
        tmp.pop_back();
      cnt++;
    }
    if (bitset<64>(tmp).to_ullong() <= k) ans = min(ans, cnt);
  }
  cout << ans << '\n';
}
