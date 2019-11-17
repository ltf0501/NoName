#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 3010;
using WInt = int64_t;

constexpr WInt kInf = 0x3f3f3f3f;

WInt g[kN][kN];
int n, m;

WInt slack[kN], lx[kN], ly[kN];

int mx[kN], my[kN], vx[kN], vy[kN], timer;

bool vis[kN];

bool Dfs(int x) {
  vx[x] = timer;
  for (int y = 1; y <= m; y++) {
    if (vy[y] == timer) continue;
    auto t = lx[x] + ly[y] - g[x][y];
    if (!t) {
      vy[y] = timer;
      if (!my[y] || Dfs(my[y])) {
        mx[x] = y;
        my[y] = x;
        return true;
      }
    } else {
      slack[y] = min(slack[y], t);
    }
  }
  return false;
}

void Reweight() {
  auto t = kInf;
  for (int y = 1; y <= m; y++) {
    if (vy[y] != timer) t = min(t, slack[y]);
  }
  for (int x = 1; x <= n; x++) {
    if (vx[x] == timer) lx[x] -= t;
  }
  for (int y = 1; y <= m; y++) {
    if (vy[y] == timer) ly[y] += t;
  }
}

WInt Km() {
  memset(lx, 0, sizeof(lx)), memset(ly, 0, sizeof(ly));
  memset(mx, 0, sizeof(mx)), memset(my, 0, sizeof(my));
  for (int x = 1; x <= n; x++) {
    lx[x] = -kInf;
    for (int y = 1; y <= m; y++) lx[x] = max(lx[x], g[x][y]);
  }
  for (int x = 1; x <= n; x++) {
    for (;;) {
      ++timer;
      memset(slack, kInf, sizeof(slack));
      if (Dfs(x))
        break;
      else
        Reweight();
    }
  }
  WInt ans = 0;
  for (int x = 1; x <= n; x++) {
    if (mx[x]) ans += g[x][mx[x]];
  }
  return ans;
}
#define F first
#define S second
long long int ABS(long long int n) { return n > 0 ? n : -n; }
long long int dist(pair<int, int> a, pair<int, int> b) {
  return ABS(a.F - b.F) + ABS(a.S - b.S);
}
int main() {
  long long int ans = 0;
  scanf("%d%d", &n, &m);
  pair<int, int> a[kN], res, b[kN];
  for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].F, &a[i].S);
  for (int i = 1; i <= m; i++) scanf("%d%d", &b[i].F, &b[i].S);
  scanf("%d%d", &res.F, &res.S);
  for (int i = 1; i <= n; i++) ans += dist(a[i], res);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      g[i][j] = -dist(a[i], b[j]);
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j < n; j++) {
      g[i][j + m] = -dist(res, a[i]);
    }
  m += n - 1;
  ans -= Km();
  printf("%lld\n", ans);
}
