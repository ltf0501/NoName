#include <bits/stdc++.h>
using namespace std;
const int maxn = 65;
const int maxc = 1400;
int n, k;
int a[maxn];
bitset<maxc> dp[maxn][maxn];
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  dp[0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    dp[i][0][0] = 1;
    for (int j = 1; j <= i; j++) {
      for (int s = 0; s < maxc; s++) {
        if (dp[i - 1][j][s]) dp[i][j][s] = 1;
        if (s - a[i] >= 0 && dp[i - 1][j - 1][s - a[i]]) dp[i][j][s] = 1;
      }
    }
  }
  double ans = -1.0;
  for (int s = 1; s <= n; s++) {
    int mx = -1;
    for (int i = k + 5 * (s + 1) - 10; i >= k - 10; i--)
      if (dp[n][s][i]) {
        mx = i;
        break;
      }
    // printf("mx = %d\n", mx);
    if (mx != -1) ans = max(ans, (double)(mx + 10 - k) / (double)(s + 1));
  }
  if (ans == -1.0)
    puts("impossible");
  else
    printf("%.10f\n", ans);
  return 0;
}
