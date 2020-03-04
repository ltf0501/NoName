#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll kInf = 1e16 + 10;
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		int n, X, Y, Z; scanf("%d%d%d%d", &n, &X, &Y, &Z);
		vector<int> s(n);
		for(int i = 0; i < n; i++) scanf("%d", &s[i]);
		vector<vector<int>> lcs(n, vector<int>(n, 0));
 
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(s[i] == s[j]) lcs[i][j] = (i > 0 && j > 0) ? lcs[i - 1][j - 1] + 1 : 1;
				else lcs[i][j] = 0;
			}
		}
		
		vector<vector<int>> pre(n, vector<int>(n, -1));
		for(int i = 0; i < n; i++) 
			for(int j = 0; j < i; j++) pre[i][min(i - j, lcs[i][j])] = j;
		for(int i = 0; i < n; i++) {
				for(int j = i - 1; j >= 0; j--) pre[i][j] = max(pre[i][j], pre[i][j + 1]);
		}
 
		vector<vector<ll>> dp(n, vector<ll>(n, kInf));
		dp[0][0] = X;
		for(int i = 1; i < n; i++) {
			dp[i][0] = dp[i - 1][0] + X;
			for(int j = 1; j <= i; j++) {
				if(pre[i][j] == -1) continue;
				dp[i][j] = min(dp[i][j], dp[pre[i][j]][j] + 1LL * (i - j - pre[i][j]) * X + Z);
				dp[i][j] = min(dp[i][j], dp[i - j][0] + Y + Z);
				dp[i][0] = min(dp[i][0], dp[i][j]);	
			} 
		}
		printf("Case #%d: %lld\n", ++cas, dp[n - 1][0]);
	}
	return 0;
}
