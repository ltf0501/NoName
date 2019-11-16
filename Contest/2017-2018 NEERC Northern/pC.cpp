#include <bits/stdc++.h>
using namespace std;

int chr2id[128];
int cnt[20][20];
string vowel = "aeiouwy";

int main() {
#ifdef ONLINE_JUDGE
  freopen("consonant.in", "r", stdin);
  freopen("consonant.out", "w", stdout);
#endif
  string str;
  cin >> str;
  int n = int(str.size());
  int ctr = 0;
  for (char c = 'a'; c <= 'z'; c++) {
    if (vowel.find(c) == string::npos) {
      chr2id[c] = ctr++;
    } else {
      chr2id[c] = 19;
    }
  }
  for (int i = 1; i < n; i++) {
    int a = chr2id[str[i - 1]], b = chr2id[str[i]];
    if (a > b) swap(a, b);
    ++cnt[a][b];
  }
  pair<int, int> ans{0, 0};
  for (int i = 0; i < (1 << ctr); i++) {
    int res = 0;
    for (int j = 0; j < ctr; j++) {
      for (int k = j + 1; k < ctr; k++) {
        if (!!(i & (1 << j)) ^ !!(i & (1 << k))) {
          res += cnt[j][k];
        }
      }
    }
    ans = max(ans, {res, i});
  }
  for (char c : str) {
    if (ans.second & (1 << chr2id[c]))
      cout << char(toupper(c));
    else
      cout << c;
  }
  cout << '\n';
}
