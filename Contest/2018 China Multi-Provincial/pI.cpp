#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int f[maxn];
int pw(int a, int n, int p) {
  int res = 1;
  while (n) {
    if (n & 1) res = 1LL * res * a % p;
    n >>= 1, a = 1LL * a * a % p;
  }
  return res;
}
int INV(int a, int p) { return pw(a, p - 2, p); }
int main() {
  int T;
  int cas = 0;
  scanf("%d", &T);
  while (T--) {
    int n, k, p;
    scanf("%d%d%d", &n, &k, &p);
    printf("Case #%d: ", ++cas);
    f[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
      f[i] = 1LL * f[i + 1] * min(k + 1, n - i) % p;
    }

    if (k >= n - 1) {
      printf("%d\n", f[0]);
      continue;
    }

    int ans = f[0];

    for (int x = 0; x < n; x++)
      if (1 + k <= n - x) {
        for (int i = 0; i < x; i++) {
          int tmp = 1;
          tmp = 1LL * f[0] * INV(f[i], p) % p * f[x] % p;
          ans = (ans + tmp) % p;
        }
      }

    for (int x = 0; x < n; x++) {
      int tmp = 1;
      tmp = 1LL * f[0] * INV(f[x], p) % p * f[x + 1] % p;
      int cnt = max(0, (n - x - 1) - (k + 2) + 1);
      tmp = 1LL * tmp * cnt % p;
      ans = (ans + tmp) % p;
    }
    printf("%d\n", ans);
  }
  return 0;
}
