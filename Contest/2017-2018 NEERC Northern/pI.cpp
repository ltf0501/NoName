#include <bits/stdc++.h>
using namespace std;
long long int ABS(long long int n) { return n >= 0 ? n : -n; }
int main() {
#ifdef ONLINE_JUDGE
  freopen("intel.in", "r", stdin);
  freopen("intel.out", "w", stdout);
#endif
  long long int l, r, u, d, n, x, y, sx, sy, lx, ly, tot = 0;
  scanf("%lld%lld%lld", &n, &lx, &ly);
  u = d = ly;
  l = r = lx;
  sx = lx;
  sy = ly;
  for (int i = 1; i < n; i++) {
    scanf("%lld%lld", &x, &y);
    l = min(l, x);
    r = max(r, x);
    u = min(u, y);
    d = max(d, y);
    tot += ABS(lx - x) + ABS(ly - y);
    lx = x;
    ly = y;
  }
  tot += ABS(x - sx) + ABS(y - sy);
  printf("%lld\n", tot - (d - u) * 2 - (r - l) * 2);
}
