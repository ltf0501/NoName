#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second
int n, m;
int in[maxn], dfs_clock;
int p[maxn];
int r, s;
bool flag;
pii low[maxn];
pii from[maxn];
vector<int> g[maxn];

vector<int> ans[3];
void init(int n) {
  dfs_clock = 0;
  for (int i = 1; i <= n; i++) g[i].clear();
  memset(in, 0, sizeof(in));
  flag = 0;
  for (int i = 0; i < 3; i++) ans[i].clear();
}
int dfs(int u, int fa) {
  p[u] = fa;
  in[u] = ++dfs_clock;

  low[u] = {dfs_clock, dfs_clock};
  for (int v : g[u])
    if (v != fa) {
      if (!in[v]) {
        int x = dfs(v, u);
        if (x < low[u].F) {
          low[u].S = low[u].F, low[u].F = x;
          from[u].S = from[u].F, from[u].F = v;
        } else if (x < low[u].S) {
          low[u].S = x, from[u].S = v;
        }
      } else {
        if (in[v] < low[u].F) {
          low[u].S = low[u].F, low[u].F = in[v];
          from[u].S = from[u].F, from[u].F = v;
        } else if (in[v] < low[u].S) {
          low[u].S = in[v], from[u].S = v;
        }
      }
    }
  if (!flag && low[u].S < in[u]) {
    ans[0].push_back(u);
    int cur = from[u].F;
    while (in[cur] != low[u].F) {
      ans[0].push_back(cur);
      cur = from[cur].F;
    }
    ans[0].push_back(cur);
    cur = from[u].S;
    ans[1].push_back(u);
    while (in[cur] != low[u].S) {
      ans[1].push_back(cur);
      cur = from[cur].F;
    }
    ans[1].push_back(cur);
    vector<int> tmp;
    while (in[cur] != low[u].F) tmp.push_back(cur), cur = p[cur];
    reverse(tmp.begin(), tmp.end());
    for (int x : tmp) ans[0].push_back(x);
    cur = u;
    while (in[cur] != low[u].S) {
      ans[2].push_back(cur);
      cur = p[cur];
    }
    ans[2].push_back(cur);
    flag = 1;
  }
  return low[u].F;
}
int main() {
#ifdef ONLINE_JUDGE
  freopen("grand.in", "r", stdin);
  freopen("grand.out", "w", stdout);
#endif
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      g[x].push_back(y), g[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
      if (!in[i]) dfs(i, -1);
    if (flag) {
      printf("%d %d\n", ans[0][0], ans[0].back());
      for (int i = 0; i < 3; i++) {
        printf("%d", (int)ans[i].size());
        for (int x : ans[i]) printf(" %d", x);
        puts("");
      }
    } else
      puts("-1");
  }
  return 0;
}
