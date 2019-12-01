#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
const int kN = 1e5 + 10;
int n, m;
vector<int> g[kN];
int in[kN], dfs_clock;
int sz[kN];
vector<pii> bcc[kN];
int bcc_cnt;
stack<int> s;
int dfs(int u, int fa) {
  int lowu = in[u] = ++dfs_clock;
  s.push(u);
  sz[u] = 1;
  for (int v : g[u])
    if (v != fa) {
      if (!in[v]) {
        int lowv = dfs(v, u);
        sz[u] += sz[v];
        lowu = min(lowu, lowv);
        if (lowv >= in[u]) {
          bcc_cnt++;
          int now, pre_sz = 0;
          do {
            now = s.top();
            s.pop();
            bcc[bcc_cnt].push_back({now, sz[now] - pre_sz});
            pre_sz = sz[now];
          } while (now != v);
          bcc[bcc_cnt].push_back({u, n - pre_sz});
        }
      } else {
        lowu = min(lowu, in[v]);
      }
    }
  return lowu;
}
ll p[kN], q[kN];
int a[kN];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y), g[y].push_back(x);
  }
  dfs(1, -1);

  ll ans = 0;
  for (int i = 1; i <= bcc_cnt; i++) {
    int k = int(bcc[i].size());
    for (int j = 0; j < k; j++) {
      a[j] = bcc[i][j].S;
      p[j] = p[j + k] = bcc[i][j].S;
      q[j] = 1LL * bcc[i][j].S * j, q[j + k] = 1LL * bcc[i][j].S * (j + k);
    }
    for (int j = 1; j < 2 * k; j++) p[j] += p[j - 1], q[j] += q[j - 1];

    for (int i = 0; i < k; i++) {
      int tmp = i + k / 2;
      if (k % 2 == 0 && i >= k / 2) tmp--;
      ans += 1LL * a[i] * (q[tmp] - q[i] - (p[tmp] - p[i]) * i);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
