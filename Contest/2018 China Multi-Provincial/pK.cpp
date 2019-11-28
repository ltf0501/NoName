#include <bits/stdc++.h>
using namespace std;

bitset<64> g[64];
int64_t cnt[1 << 19], weight[64];
int64_t cnt2[1 << 19];

int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int tt = 1; tt <= t; tt++) {
    memset(cnt, 0, sizeof(cnt));
    memset(cnt2, 0, sizeof(cnt2));
    vector<pair<int, int>> left;
    cout << "Case #" << tt << ": ";
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
      g[i].reset();
      cin >> weight[i];
    }
    while (m--) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u][v] = g[v][u] = true;
    }
    int lh = n / 2, rh = n - lh;
    for (int i = 0; i < (1 << lh); i++) {
      int need_mask = 0;
      int64_t prod = 1;
      for (int j = 0; j < lh; j++) {
        if (i & (1 << j)) {
          prod = prod * weight[j] % q;
        } else {
          for (int k = 0; k < lh; k++) {
            if (g[j][k] && (~i & (1 << k))) goto Cont1;
          }
          for (int k = lh; k < n; k++) {
            if (g[j][k]) need_mask |= 1 << (k - lh);
          }
        }
      }
      cnt[need_mask] = (cnt[need_mask] + prod) % q;
    Cont1:;
    }
    for (int j = 0; j < rh; j++) {
      for (int i = 0; i < (1 << rh); i++) {
        if (i & (1 << j)) cnt[i] = (cnt[i] + cnt[i ^ (1 << j)]) % q;
      }
    }
    // for (int i = 0; i < (1 << lh); i++) {
    //	for (int j = 0; j < lh; j++) {
    //		if (~i & (1 << j)) {
    //			int mul = (__builtin_popcount(i) & 1) ? (q - 1) : 1;
    //			cnt2[i | (1 << j)] = (cnt2[i | (1 << j)] + mul * cnt[i]) %
    //q;
    //		}
    //	}
    //}
    int64_t ans = 0;
    for (int i = 0; i < (1 << rh); i++) {
      int64_t prod = 1;
      for (int j = 0; j < rh; j++) {
        if (i & (1 << j)) {
          prod = prod * weight[j + lh] % q;
        } else {
          for (int k = 0; k < rh; k++) {
            if (g[j + lh][k + lh] && (~i & (1 << k))) goto Cont2;
          }
        }
      }
      ans = (ans + prod * cnt[i]) % q;
    Cont2:;
    }
    cout << ans << '\n';
  }
}
