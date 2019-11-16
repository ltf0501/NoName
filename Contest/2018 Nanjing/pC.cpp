#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int INF = 1e9;
#define F first
#define S second
int n, ans;
vector<int> g[maxn];
vector<int> now;
bool vis[maxn];
int sz[maxn], mx[maxn];
int o = -1;
void get_cen(int u, int fa) {
  now.push_back(u);
  sz[u] = 1;
  mx[u] = 0;
  for (int v : g[u])
    if (v != fa && (o == -1 ? !vis[v] : v != o)) {
      get_cen(v, u);
      sz[u] += sz[v];
      mx[u] = max(mx[u], sz[v]);
    }
}
pair<int, int> dfs(int u) {
  now.clear();
  get_cen(u, -1);
  int cen = -1;
  for (int x : now) {
    if (2 * max(mx[x], sz[u] - sz[x]) <= sz[u]) cen = x;
  }
  return make_pair(sz[u], cen);
}
int cal_ans(int u) {
  int cur = INF;
  int id = -1;
  o = u;
  for (int v : g[u]) {
    pair<int, int> res = dfs(v);
    int tmp = n - res.F + max(mx[res.S], sz[v] - sz[res.S]);
    if (tmp < cur) cur = tmp, id = v;
  }
  ans = max(ans, cur);
  // printf("u = %d, cur = %d, id = %d\n", u, cur, id);
  o = -1;
  return id;
}
void solve(int u) {
  while (!vis[u]) {
    int cen = dfs(u).S;
    vis[cen] = 1;
    u = cal_ans(cen);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y), g[y].push_back(x);
  }
  solve(1);
  printf("%d\n", ans);
  return 0;
}
