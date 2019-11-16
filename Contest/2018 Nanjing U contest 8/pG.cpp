#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
#define pii pair<int, int>
#define F first
#define S second
#define ll long long
const int mod = 998244353;
vector<pii> g[maxn];
vector<int> vv[maxn];
int p[maxn], sz[maxn], e[maxn];
int finds(int x) { return p[x] == x ? x : p[x] = finds(p[x]); }
int in[maxn], out[maxn], dfs_clock;
int pre[maxn];
int deg[maxn];
bool vis[maxn];
void dfs1(int u, int fa) {
  in[u] = ++dfs_clock;
  for (pii v : g[u])
    if (v.F != fa) {
      dfs1(v.F, u);
      if (v.S == 1) {
        pre[in[v.F]]++;
        pre[out[v.F] + 1]--;
      } else {
        pre[1]++;
        pre[in[v.F]]--;
        pre[out[v.F] + 1]++;
      }
    }
  out[u] = dfs_clock;
}
void dfs2(int u, vector<int>& cc) {
  cc.push_back(u);
  vis[u] = 1;
  for (pii v : g[u])
    if (!vis[v.F]) {
      dfs2(v.F, cc);
      break;
    }
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int N = 2 * n;
    for (int i = 1; i <= N; i++) g[i].clear(), vv[i].clear();
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1, e[i] = 0;
    for (int i = 1; i <= n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      g[x].push_back(pii(y, 0));
      g[y].push_back(pii(x, 1));
      x = finds(x), y = finds(y);
      if (x != y) {
        if (sz[x] < sz[y]) swap(x, y);
        p[y] = x, sz[x] += sz[y], e[x] += e[y] + 1;
      } else
        e[x]++;
    }
    bool flag = 1;
    for (int i = 1; i <= N; i++)
      if (finds(i) == i && e[i] > sz[i]) {
        flag = 0;
        break;
      }
    if (!flag) {
      puts("-1 -1");
      continue;
    }
    int ans = 0;
    ll tot = 1;
    for (int i = 1; i <= N; i++) vv[finds(i)].push_back(i);
    for (int i = 1; i <= N; i++)
      if (p[i] == i) {
        if (sz[i] == e[i]) {
          queue<int> q;
          for (int u : vv[i]) {
            deg[u] = (int)g[u].size();
            if (deg[u] == 1) q.push(u);
            vis[u] = 0;
          }
          while (!q.empty()) {
            int t = q.front();
            q.pop();
            if (vis[t]) continue;
            vis[t] = 1;
            for (pii v : g[t]) {
              if (deg[v.F] > 1) {
                deg[v.F]--;
                if (deg[v.F] == 1) q.push(v.F);
                ans += v.S;
              }
            }
          }
          int rt = -1, cir_sz = 0, cnt = 0;
          for (int u : vv[i])
            if (!vis[u]) {
              rt = u, cir_sz++;
            }
          vector<int> cyc;
          dfs2(rt, cyc);
          int m = (int)cyc.size();
          for (int j = 0; j < m; j++) {
            int a = cyc[j], b = cyc[(j + 1) % m];
            for (pii v : g[a])
              if (v.F == b) cnt += v.S;
          }
          if (m == 1)
            cnt = 0;
          else if (m == 2) {
            int a = cyc[0], b = cyc[1];
            int c = 0;
            for (pii v : g[a])
              if (v.F == b) c += v.S;
            if (c == 0 || c == 2)
              cnt = 1;
            else
              cnt = 0;
          }
          if (cnt == cir_sz - cnt)
            ans += cnt, tot = tot * 2 % mod;
          else
            ans += min(cnt, cir_sz - cnt);
        } else {
          dfs_clock = 0;
          dfs1(i, -1);
          for (int j = 1; j <= dfs_clock; j++) pre[j] += pre[j - 1];
          int mn = 1e9, cnt = 0;
          for (int j = 1; j <= dfs_clock; j++) {
            if (mn > pre[j])
              mn = pre[j], cnt = 1;
            else if (mn == pre[j])
              cnt++;
          }
          ans += mn;
          tot = tot * cnt % mod;
          for (int j = 1; j <= dfs_clock + 1; j++) pre[j] = 0;
        }
      }
    printf("%d %lld\n", ans, tot);
  }
  return 0;
}
