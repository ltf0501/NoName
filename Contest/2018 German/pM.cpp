#include <bits/stdc++.h>
using namespace std;
const int maxn = 505;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
typedef pair<int, int> pii;
#define F first
#define S second
int n, m, q;
bool ok(int i, int j) { return i >= 0 && i < n && j >= 0 && j < m; }
int get_id(int i, int j) { return i * m + j; }
pii gg(int x) { return {x / m, x % m}; }
int s[maxn][maxn];
bool vis[maxn * maxn];
vector<int> pos[1000010];
int p[maxn * maxn], sz[maxn * maxn];
vector<int> com[maxn * maxn];
vector<pii> que[maxn * maxn];
int ans[100010];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
void Union(int x, int y, int now) {
  // printf("now = %d, x = %d, y = %d\n", now, x, y);
  x = find(x), y = find(y);
  if (x == y) return;
  if (sz[x] < sz[y]) swap(x, y);
  for (int u : com[y]) {
    for (pii v : que[u]) {
      // printf("%d %d\n", u, v.F);
      if (find(v.F) == x) ans[v.S] = now;
    }
  }
  for (int u : com[y]) com[x].push_back(u);
  p[y] = x, sz[x] += sz[y];
}
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      scanf("%d", &s[i][j]), pos[s[i][j]].push_back(get_id(i, j));
  }
  for (int i = 0; i < q; i++) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    a--, b--, c--, d--;
    int x = get_id(a, b), y = get_id(c, d);
    que[x].push_back({y, i}), que[y].push_back({x, i});
    if (x == y) ans[i] = s[a][b];
  }
  for (int i = 0; i < n * m; i++) p[i] = i, sz[i] = 1, com[i].push_back(i);
  for (int i = 1; i <= 1000000; i++) {
    for (int x : pos[i]) vis[x] = 1;
    for (int x : pos[i]) {
      int a, b;
      tie(a, b) = gg(x);
      for (int j = 0; j < 4; j++) {
        int c = a + dx[j], d = b + dy[j];
        if (!ok(c, d)) continue;
        int y = get_id(c, d);
        if (vis[y]) Union(x, y, i);
      }
    }
  }
  for (int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
