#include <stdio.h>
const int N = 1e2 + 10;
const int M = 1e3 + 10;
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a > b ? b : a; }
int a[N], val[M], dp[N][M], tot = 0;
int f(int n, int m) {
  if (n <= 0) return 0;
  if (m < 0) return 0;
  if (dp[n][m] > 0) return dp[n][m];
  if (m > tot) return 0;
  int ans = 0;
  if (m == 0) {
    ans = f(n - 1, m + 1);
    for (int i = 0; i <= tot; i++) ans = max(ans, f(n - 2, i));
  } else
    ans = max(f(n - 1, m - 1) + min(a[n - 1], val[m - 1]), f(n - 1, m + 1));
  //	printf("dp[%d][%d]=%d\n",n,m,ans);
  return dp[n][m] = ans;
}
int main() {
  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  while (m) {
    val[tot++] = m;
    m <<= 1;
    m /= 3;
  }
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= tot; j++) dp[i][j] = 0;
  for (int i = 0; i <= tot; i++) ans = max(ans, f(n, i));
  printf("%d\n", ans);
}
