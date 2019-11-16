#include <bits/stdc++.h>
using namespace std;
int n, sz[100001], ans[100001];
set<int> st[100001];
set<pair<int, int>> query[100001];
vector<int> g[100001];
void dfs(int x, int p) {
  sz[x] = 1;
  pair<int, int> mxSz = {0, -1};
  for (int y : g[x]) {
    if (y == p) continue;
    dfs(y, x);
    sz[x] += sz[y];
    mxSz = max(mxSz, {sz[y], y});
  }
  if (sz[x] == 1) {
    st[x].insert(x);
    for (auto qu : query[x]) {
      ans[qu.second] = qu.first == x ? n : 1;
    }
    return;
  }
  for (int y : g[x]) {
    if (y == mxSz.second) {
      st[x] = move(st[y]);
      for (auto qu : query[x]) {
        if (st[x].find(qu.first) != st[x].end()) {
          ans[qu.second] = n - sz[y];
        }
      }
    }
  }
  for (int y : g[x]) {
    if (y != mxSz.second) {
      for (auto e : st[y]) {
        st[x].insert(e);
        auto it = query[x].lower_bound({e, 0});
        if (it != query[x].end() && it->first == e) {
          ans[it->second] = n - sz[y];
        }
      }
    }
  }
  st[x].insert(x);
  for (auto qu : query[x]) {
    if (!ans[qu.second]) {
      if (qu.first == x)
        ans[qu.second] = n;
      else
        ans[qu.second] = sz[x];
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int t;
  cin >> t;
  for (int cases = 1; cases <= t; cases++) {
    int q, r;
    cin >> n >> q >> r;
    for (int i = 1; i <= n; i++) g[i].clear(), st[i].clear(), query[i].clear();
    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 0; i < q; i++) {
      int s, nn;
      cin >> s >> nn;
      if (s == 0) {
        r = nn;
        ans[i] = -1;
      } else {
        query[nn].emplace(r, i);
        ans[i] = 0;
      }
    }
    dfs(1, -1);
    cout << "Case #" << cases << ":\n";
    for (int i = 0; i < q; i++) {
      if (ans[i] != -1) cout << ans[i] << '\n';
    }
  }
}
