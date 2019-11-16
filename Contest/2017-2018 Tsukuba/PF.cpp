#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 9;
#define maxn 100010
#define ll long long
#define pli pair<ll, int>
#define mk make_pair
#define F first
#define S second
const ll INF = 1e14;
struct edge {
  int u, v, d;
};
int n, m;
vector<edge> e;
vector<int> g[maxn], g2[maxn], dag[maxn];
bool isdag[maxn];
int to(int x, int id) { return x ^ e[id].u ^ e[id].v; }
ll dis[2][maxn];
ll num[2][maxn];
bool vis[maxn];
void dijk(int s, vector<int> *g, ll *d, ll *f) {
  for (int i = 1; i <= n; i++) d[i] = INF;
  memset(vis, 0, sizeof(vis));
  priority_queue<pli, vector<pli>, greater<pli> > pq;
  pq.push(mk(d[s] = 0, s));
  f[s] = 1;
  while (!pq.empty()) {
    pli t = pq.top();
    pq.pop();
    if (vis[t.S]) continue;
    for (int id : g[t.S]) {
      int v = to(t.S, id);
      if (d[v] > t.F + e[id].d) {
        d[v] = t.F + e[id].d;
        pq.push(mk(d[v], v));
        f[v] = f[t.S];
      } else if (d[v] == t.F + e[id].d)
        f[v] = (f[v] + f[t.S]) % mod;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int sz = (int)e.size();
    e.push_back({a, b, c});
    g[a].push_back(sz), g2[b].push_back(sz);
  }
  dijk(1, g, dis[0], num[0]), dijk(2, g2, dis[1], num[1]);
  ll tot = dis[0][2];
  //	for(int i=1;i<=n;i++)printf("%lld ",num[0][i]);puts("");
  //	for(int i=1;i<=n;i++)printf("%lld ",num[1][i]);puts("");
  //	for(int i=1;i<=n;i++)printf("%lld ",dis[0][i]);puts("");
  //	for(int i=1;i<=n;i++)printf("%lld ",dis[1][i]);puts("");
  for (int i = 0; i < m; i++) {
    if (dis[0][e[i].u] + e[i].d + dis[1][e[i].v] == tot) isdag[i] = 1;
  }

  for (int i = 0; i < m; i++) {
    if (!isdag[i]) {
      if (dis[0][e[i].v] + e[i].d + dis[1][e[i].u] < tot)
        puts("HAPPY");
      else
        puts("SOSO");
    } else {
      if (1ll * num[0][e[i].u] * num[1][e[i].v] == num[0][2])
        puts("SAD");
      else
        puts("SOSO");
    }
  }
  return 0;
}
