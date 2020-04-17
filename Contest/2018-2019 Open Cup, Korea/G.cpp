#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 2.5e5 + 10;
const int kC = 10;
const ll kInf = 1e17;

ll dp[2][2][2][kC][kC]; //(n, f_n - 1, f_n, x, y)
int n, k;
int w[kN];
void gao(ll &a, ll b) {
	a = min(a, b);
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1][0][0][0] = 0;
	int cur = 0;
	for(int i = 1; i <= n; i++) {
		int pre = cur;
		cur ^= 1;
		memset(dp[cur], 0x3f, sizeof(dp[cur]));

		for(int a = 0; a <= k; a++) for(int b = 0; b <= k; b++) for(int x = 0; x < 2; x++) for(int y = 0; y < 2; y++) {
			if(dp[pre][x][y][a][b] > kInf) continue;
			ll pre_dp = dp[pre][x][y][a][b];

			gao(dp[cur][y][1][a][b], pre_dp + w[i]);
			if(x || y) gao(dp[cur][y][0][a][b], pre_dp);
			if(b < k) gao(dp[cur][y][1][a][b + 1], pre_dp);
			if(a < k && (x || y)) gao(dp[cur][y][0][a + 1][b], pre_dp + w[i]);
		}
	}

	ll ans = kInf;
	for(int i = 0; i <= k; i++) for(int x = 0; x < 2; x++) for(int y = 0; y < 2; y++) 
		if(x || y) gao(ans, dp[cur][x][y][i][i]);
	printf("%lld\n", ans);
	return 0;
}
