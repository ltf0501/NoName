#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int> g[maxn];
set<int> s[maxn];
int ans[maxn];
int col[maxn];
int in[maxn], out[maxn], dfs_clock, dep[maxn];
int anc[20][maxn];
int euler[maxn];
void dfs(int u, int fa, int d) {
  anc[0][u] = fa;
  in[u] = ++dfs_clock;
  euler[dfs_clock] = u;
  dep[u] = d;
  s[col[u]].insert(dfs_clock);
  for (int v : g[u])
    if (v != fa) {
      dfs(v, u, d + 1);
    }
  out[u] = dfs_clock;
}
bool ancestor(int x, int y) { return in[x] <= in[y] && out[x] >= out[y]; }
int LCA(int x, int y) {
  if (ancestor(x, y)) return x;
  if (ancestor(y, x)) return y;
  for (int i = 17; i >= 0; i--)
    if (!ancestor(anc[i][x], y)) x = anc[i][x];
  return anc[0][x];
}
int dis(int x, int y) {
  int z = LCA(x, y);
  int res = dep[x] + dep[y] - 2 * dep[z];
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y), g[y].push_back(x);
  }
  for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
  dfs(1, 0, 0);
  out[0] = dfs_clock;
  for (int j = 1; j <= 17; j++)
    for (int i = 1; i <= n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];
  for (int i = 1; i < maxn; i++) {
    if (s[i].size() >= 2) {
      auto it = s[i].begin();
      while (next(it) != s[i].end())
        ans[i] += dis(euler[*it], euler[*next(it)]), ++it;
      ans[i] += dis(euler[*it], euler[*s[i].begin()]);
    }
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    char c[2];
    scanf("%s", c);
    if (c[0] == 'U') {
      int x, y;
      scanf("%d%d", &x, &y);
      if (col[x] == y) continue;
      int u = col[x];
      s[u].erase(in[x]);
      if (!s[u].empty()) {
        auto it = s[u].lower_bound(in[x]);
        int prv = (it == s[u].begin() ? *prev(s[u].end()) : *prev(it));
        int nxt = (it == s[u].end() ? *s[u].begin() : *it);
        prv = euler[prv], nxt = euler[nxt];
        ans[u] -= dis(prv, x), ans[u] -= dis(x, nxt);
        ans[u] += dis(prv, nxt);
      }
      if (!s[y].empty()) {
        auto it = s[y].lower_bound(in[x]);
        int prv = (it == s[y].begin() ? *prev(s[y].end()) : *prev(it));
        int nxt = (it == s[y].end() ? *s[y].begin() : *it);
        prv = euler[prv], nxt = euler[nxt];
        ans[y] += dis(prv, x), ans[y] += dis(x, nxt);
        ans[y] -= dis(prv, nxt);
      }
      s[y].insert(in[x]);
      col[x] = y;
    } else {
      int x;
      scanf("%d", &x);
      if (s[x].size() == 0)
        puts("-1");
      else
        printf("%d\n", ans[x] / 2);
    }
  }
  return 0;
}
