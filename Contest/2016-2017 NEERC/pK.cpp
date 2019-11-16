#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 3e5 + 10;
int p[N];
long long int a[N], b[N], ans[N], val[N], cost[N];
int find(int n) { return p[n] == n ? n : p[n] = find(p[n]); }
void merge(int l, int r, long long int c) {
  val[l] = min(val[l], val[r]);
  cost[l] = max(max(cost[l], cost[r]), c);
  ans[l] = min(val[l] * cost[l], ans[l] + ans[r]);
  p[r] = l;
  return;
}
int main() {
  vector<pair<int, pair<int, int>>> v;
  int n, m, l, r, c;
  long long int out = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%lld%lld", &cost[i], &val[i]);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &l, &r, &c);
    v.PB({c, {l, r}});
  }
  for (int i = 1; i <= n; i++) p[i] = i;
  for (int i = 1; i <= n; i++) ans[i] = val[i] * cost[i];
  sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); i++) {
    l = v[i].S.F;
    r = v[i].S.S;
    l = find(l);
    r = find(r);
    if (l == r) continue;
    c = v[i].F;
    merge(l, r, c);
  }
  for (int i = 1; i <= n; i++)
    if (p[i] == i) out += ans[i];
  printf("%lld\n", out);
}
