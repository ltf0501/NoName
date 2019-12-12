#include <stdio.h>
 
constexpr int kN = int(1E2 + 10), kC = int(1E4 + 10);
 
long double dp[kN][kC], f[kN];
int a[kN];
 
void pre() {
	f[0] = f[1] = 1;
	for (int i = 2; i < kN; i++) f[i] = f[i - 1] * i;
	return ;
}
 
long double C(int n, int m) {return f[n] / f[m] / f[n - m];}
 
int main() {
	pre();
	int n, x, tot = 0, nt = 0;
	long double ans = 0;
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) tot += a[i];
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) for (int j = n; j >= 1; j--) for (int k = a[i]; k <= tot; k++) dp[j][k] += dp[j - 1][k - a[i]];
//	for (int i = n - 1; i >= 0; i--) for (int j = 0; j <= tot; j++) if (dp[i][j] > 0) printf("dp[%d][%d] = %.3lf\n", i, j, (double)dp[i][j]);
	for (int i = n; i >= 1; i--) for (int j = 0; j <= tot; j++) 
		ans += dp[i][j] / C(n, i) * ((x * (n + i) >= j * 2) ? (double) j / (double) i : ((double) n / (double) i + 1) * (double) x / 2);
	printf("%.20lf\n", (double) ans);
}
