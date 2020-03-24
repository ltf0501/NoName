#include <bits/stdc++.h>
using namespace std;
const int kN = 18;
const int kMod = 1e8 + 7;
 
int m, n;
int l[1 << kN], r[1 << kN];
 
int dp[kN][kN];
int pre[kN][kN], pre_sum[kN][kN];
int sum[kN][kN];
int lcp[1 << kN];
 
int LCP(int x, int y) {
	for(int i = 0; i <= m; i++)
		if((x >> i) == (y >> i)) return m - i;
	//printf("x = %d, y = %d\n", x, y);
	return 0;
}
 
void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &m, &n);
		for(int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
		for(int i = 1; i <= n; i++) lcp[i] = LCP(l[i], r[i - 1]);
 
 
			for(int j = 0; j <= m; j++)
				for(int k = 0; k <= m; k++) dp[j][k] = 0;
		for(int x = l[1]; x <= r[1]; x++) add(dp[LCP(x, l[1])][LCP(x, r[1])] , x);
		for(int j = 0; j <= m; j++) {
			for(int k = 0; k <= m; k++) {
				sum[j][k] = (j ? sum[j - 1][k] : 0) + (k ? sum[j][k - 1] : 0) - (j && k ? sum[j - 1][k - 1] : 0);
				sum[j][k] %= kMod;
				if(sum[j][k] < 0) sum[j][k] += kMod;
				add(sum[j][k], dp[j][k]);
			}
		}
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= m; k++) pre[j][k] = dp[j][k], pre_sum[j][k] = sum[j][k];
 
		for(int i = 2; i <= n; i++) {
			//printf("lcp[%d] = %d\n", i, lcp[i]);
			for(int j = 0; j <= m; j++)
				for(int k = 0; k <= m; k++) dp[j][k] = 0;
			for(int x = l[i]; x <= r[i]; x++) {
				int j = LCP(x, l[i]), k = LCP(x, r[i]);
				int nxt;
				nxt = pre_sum[m][m];
				if(j > lcp[i]) {
					nxt = pre_sum[m][m] - (lcp[i] ? pre_sum[m][lcp[i] - 1] : 0);
				}
				else {
					nxt = pre_sum[m][j] - (j ? pre_sum[m][j - 1] : 0);
				}
				nxt %= kMod;
				if(nxt < 0) nxt += kMod;
				nxt = 1LL * nxt * x % kMod;
				bool flag = lcp[i] >= j;
 
				//printf("dp[%d][%d][%d] <- x = %d, flag = %d, nxt = %d\n", i, j, k, x, flag, nxt);
				add(dp[j][k], nxt);
			} 
			//sum[0][0] = dp[0][0];
			for(int j = 0; j <= m; j++) {
				for(int k = 0; k <= m; k++) {
					sum[j][k] = (j ? sum[j - 1][k] : 0) + (k ? sum[j][k - 1] : 0) - (j && k ? sum[j - 1][k - 1] : 0);
					sum[j][k] %= kMod;
					if(sum[j][k] < 0) sum[j][k] += kMod;
					add(sum[j][k], dp[j][k]);
				}
			}
			for(int j = 0; j <= m; j++)
				for(int k = 0; k <= m; k++) pre[j][k] = dp[j][k], pre_sum[j][k] = sum[j][k];
		}
 
		int ans = 0;
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= m; k++) add(ans, dp[j][k]);
		printf("%d\n", ans);
	}
	return 0;
}
