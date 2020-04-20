#include <stdio.h>
constexpr int kN = int(5E4 + 10);


int t[kN];
double d[kN], u[kN], p[kN][101], tp[101][2], s[kN][101], dp[3][2];

int main() {
	int n;
	double ans = 0;
	bool f = true;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%lf%lf", &t[i], &d[i], &u[i]);
	for (int i = 1; i <= n; i++) {
		t[i] *= 5;
		for (int j = 1; j <= 20; j++) tp[j][!f] = 0;
		tp[0][!f] = 1;
		for (int j = 1; j <= 10; j++) {
			tp[0][f] = tp[0][!f] * d[i];
			for (int k = 1; k < j; k++) tp[k][f] = tp[k][!f] * d[i] + tp[k - 1][!f] * (1 - d[i]);
			tp[j][f] = tp[j - 1][!f] * (1 - d[i]);
			f = !f;
		}
		for (int j = 11; j <= 20; j++) {
			tp[0][f] = tp[0][!f] * u[i];
			for (int k = 1; k < j; k++) tp[k][f] = tp[k][!f] * u[i] + tp[k - 1][!f] * (1 - u[i]);
			tp[j][f] = tp[j - 1][!f] * (1 - u[i]);
			f = !f;
		}
		for (int j = 0; j <= 20; j++) p[i][j] = tp[j][!f];
		s[i][0] = p[i][0];
		for (int j = 1; j <= 20; j++) s[i][j] = s[i][j - 1] + p[i][j];
	}

	for (int i = 0; i <= 20; i++) {
		dp[0][!f] = p[1][i];
		dp[1][!f] = dp[2][!f] = 0;
		for (int j = 2; j <= n; j++) {
			if (t[1] + i * 60 > t[j] + 1200) {
				dp[0][f] = 0;
				dp[1][f] = dp[0][!f];
				dp[2][f] = dp[1][!f];
			}
			else if (t[j] >= t[1] + i * 60) f = !f;
			else {
				double np = s[j][(t[1] + i * 60 - t[j] + 59) / 60 - 1], nq = 1 - np;
				dp[0][f] = dp[0][!f] * nq;
				dp[1][f] = dp[0][!f] * np + dp[1][!f] * nq;
				dp[2][f] = dp[1][!f] * np + dp[2][!f] * nq;
			}
			f = !f;
		}
		ans += dp[0][!f] + dp[1][!f] + dp[2][!f];
	}
	printf("%.20lf\n", ans);
}