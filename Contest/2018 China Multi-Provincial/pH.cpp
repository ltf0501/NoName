#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
#define F first
#define S second
long long int val(long long int n) { return n * (n + 1) / 2; }
int tox(int n) {
  long long int l = 0, r = n, mid;
  while (r - l > 1) {
    mid = (l + r) >> 1;
    if (val(mid) >= n)
      r = mid;
    else
      l = mid;
  }
  return (int)r;
}
const int N = 1e5 + 10;
pair<double, int> p[N];
int x[N], y[N];
;
void solve() {
  int n;
  long long int ans = 0, now = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
  for (int i = 1; i <= n; i++) x[i] = tox(x[i]);
  for (int i = 1; i <= n; i++) p[i] = {(double)x[i] / y[i], i};
  sort(p + 1, p + n + 1);
  for (int i = 1; i <= n; i++) {
    now += x[p[i].S];
    ans += now * y[p[i].S];
  }
  printf("%lld\n", ans);
}
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }
}
