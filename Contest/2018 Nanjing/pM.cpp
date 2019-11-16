#include <bits/stdc++.h>
using namespace std;
constexpr int kA1 = 31, kA2 = 59, kMod = 1E9 + 7, kN = 1000010;
int a1pow[kN], a2pow[kN], h1f[kN], h2f[kN], h1b[kN], h2b[kN], pref[kN],
    z[kN * 2];
string ss, tt;
void zalg(string str) {
  int l = 0, r = 0, len = int(str.size());
  for (int i = 0; i < len; i++) {
    if (i > r) {
      l = r = i;
      while (r < len && str[r] == str[r - l]) ++r;
      z[i] = r - l;
      --r;
    } else {
      if (z[i - l] < r - i + 1) {
        z[i] = z[i - l];
      } else {
        l = i;
        while (r < len && str[r] == str[r - l]) ++r;
        z[i] = r - l;
        --r;
      }
    }
  }
}
int zz[kN * 2];
int zzz[kN], zzzz[kN];
void manacher(const string& s) {
  string t = ".";
  for (int i = 0; i < s.length(); ++i) t += s[i], t += '.';
  int l = 0, r = 0;
  for (int i = 1; i < t.length(); ++i) {
    zz[i] = (r > i ? min(zz[2 * l - i], r - i) : 1);
    while (i - zz[i] >= 0 && i + zz[i] < t.length() &&
           t[i - zz[i]] == t[i + zz[i]])
      ++zz[i];
    if (i + zz[i] > r) r = i + zz[i], l = i;
  }
  for (int i = 1; i <= s.length(); i++) {
    zzz[i] = zz[2 * i - 1] / 2;
    zzzz[i] = zz[2 * i] / 2;
  }
}
int main() {
  cin >> ss >> tt;
  int n = ss.size();
  reverse(ss.begin(), ss.end());
  manacher(ss);
  for (int i = 1; i <= ss.length(); i++) {
    pref[i]++, pref[i + zzz[i]]--;
    pref[i + 1]++, pref[i + zzzz[i] + 1]--;
  }
  for (int i = 1; i <= int(ss.size()); i++) pref[i] += pref[i - 1];
  zalg(tt + "X" + ss);
  string tmp = tt + "X" + ss;
  priority_queue<int> pq;
  int64_t ans = 0;
  for (int i = 1, idx = int(tt.size()) + 1; i < int(ss.size()); i++, idx++) {
    ans += 1LL * pref[i] * z[idx + 1];
  }
  cout << ans << '\n';
}
