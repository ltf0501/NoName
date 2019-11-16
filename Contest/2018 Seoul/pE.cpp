#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 3e5 + 10;
const double INF = 1e9 + 10;
pair<int, int> p[N];
int n;
int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }
bool ok(double range) {
  int now = 0, last, low, top, lt, ll;
  while (now < n) {
    if (p[now].S <= range)
      now++;
    else
      break;
  }
  if (now == 0 && p[0].F == 0) return 0;
  low = p[now].S;
  top = p[now].S;
  while (now < n) {
    low = min(low, p[now].S);
    top = max(top, p[now].S);
    if (top - low <= range * 2)
      now++;
    else
      break;
    ll = low;
    lt = top;
  }
  int mi = top - range, mx = low + range;
  low = p[now].S;
  top = p[now].S;
  while (now < n) {
    low = min(low, p[now].S);
    top = max(top, p[now].S);
    if (top - low > range * 2) break;
    if (low + range >= mi)
      now++;
    else
      break;
  }
  return now >= n;
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d%d", &p[i].F, &p[i].S);
  sort(p, p + n);
  int l = 0, r = 2e9 + 10;
  while (l < r) {
    int m = (l + r) >> 1;
    if (ok(m * 1.0 / 2.0))
      r = m;
    else
      l = m + 1;
  }
  if (l & 1)
    printf("%d.5\n", l >> 1);
  else
    printf("%d.0\n", l >> 1);
}
