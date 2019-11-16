#include <stdio.h>
const int MOD = 998244353;
const int N = 2e5 + 10;
long long int f[N], inv[N];
long long int pow(long long int a, long long int b) {
  long long int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
      ans %= MOD;
    }
    a *= a;
    a %= MOD;
    b >>= 1;
  }
  return ans;
}
long long int rev(long long int n) { return pow(n, MOD - 2) % MOD; }
long long int C(int n, int m) {
  return (f[n] * inv[m] % MOD * inv[n - m]) % MOD;
}
long long int H(int n, int m) { return C(n + m - 1, m); }
int main() {
  int t, n, m, k;
  long long int ans, now;
  scanf("%d", &t);
  f[0] = 1;
  for (int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i;
    f[i] %= MOD;
  }
  inv[N - 1] = rev(f[N - 1]);
  for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
  printf("%lld\n", C(20, 12));
  while (t--) {
    scanf("%d%d%d", &n, &m, &k);
    now = 1;
    ans = 0;
    for (int i = 0; i * n <= k && i <= m; i++) {
      ans += now * C(m, i) * H(m, k - n * i) % MOD;
      ans %= MOD;
      now = -now;
    }
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
  }
}
