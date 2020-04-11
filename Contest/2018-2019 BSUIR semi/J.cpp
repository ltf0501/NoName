#include <bits/stdc++.h>
using namespace std;

using D = double;

struct Person {
	int taime;
	D down, up;
} p[500010];

D dp[500010][3], cc[610][610], eq[500010][101], ge[500010][101];
bool vis[500010][101], vis_eq[500010][101];

D C(int n, int m) {
	if (m == 0 || m == n) return 1;
	if (cc[n][m]) return cc[n][m];
	return cc[n][m] = C(n, m - 1) * (n - m + 1) / m;
}

// P(t_i = k)
D CalcProbEqConst(int i, int k) {
	if (k > 100 || k < 0) return 0;
	if (vis_eq[i][k]) return eq[i][k];
	vis_eq[i][k] = true;
	D ans = 0;
	for (int a = 0; a <= k; a++) {
		if (0 <= a && a <= 50 && 0 <= k - a && k - a <= 50) {
			ans += C(50, a) * C(50, k - a) * pow(p[i].down, a) * pow(1 - p[i].down, 50 - a) * pow(p[i].up, k - a) * pow(1 - p[i].up, 50 - k + a);
		}
	}
	return eq[i][k] = ans;
}


// P(t_i >= k)
D CalcProbGeConst(int i, int k) {
	if (k > 100) return 0;
	if (k < 0) return 1;
	if (vis[i][k]) return ge[i][k];
	vis[i][k] = true;
	return ge[i][k] = CalcProbEqConst(i, k) + CalcProbGeConst(i, k + 1);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i].taime >> p[i].down >> p[i].up;
		p[i].down = 1 - p[i].down;
		p[i].up = 1 - p[i].up;
	}
	D ans = 0;
	for (int t = p[0].taime; t <= p[0].taime + 100; t++) {
		dp[0][0] = 1;
		for (int i = 1; i < n; i++) {
			D w = CalcProbGeConst(i, t - p[i].taime);
			//cerr << t - p[i].taime << ' ' << w << '\n';
			dp[i][0] = dp[i - 1][0] * w;
			dp[i][1] = dp[i - 1][1] * w + dp[i - 1][0] * (1 - w);
			dp[i][2] = dp[i - 1][2] * w + dp[i - 1][1] * (1 - w);
		}
		cerr << t << ' ' << dp[n - 1][0] + dp[n - 1][1] + dp[n - 1][2] << endl;
		ans += CalcProbEqConst(0, t - p[0].taime) * (dp[n - 1][0] + dp[n - 1][1] + dp[n - 2][2]);
	}
	cout << ans << '\n';
}
