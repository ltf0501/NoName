#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 1E16 + 10;

int n, m, k, r;
int len[300], s[300], c[300];
int64_t dp[300][300];

int64_t dfs(int nn, int mm) {
	if (nn == n) return mm == 1 ? 0 : INF;
	if (dp[nn][mm]) return dp[nn][mm];
	dp[nn][mm] = INF;
	for (int i = 1; i <= m; i++) {
		int64_t need = 1LL * k * abs(mm - i);
		if (len[nn] >= need) {
			dp[nn][mm] = min(dp[nn][mm], int64_t(dfs(nn + 1, i) + 1LL * r * abs(mm - i) + len[nn] + s[nn] + 1LL * c[nn] * i));
		}
	}
	return dp[nn][mm];
}

int main() {
	cin >> n >> m >> k >> r;
	for (int i = 0; i < n; i++) cin >> len[i];
	for (int i = 0; i < n - 1; i++) cin >> s[i] >> c[i];
	cout << dfs(0, 1) << '\n';
}
