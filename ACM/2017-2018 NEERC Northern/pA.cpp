#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int dp[maxn]; 
int main() {
#ifdef ONLINE_JUDGE
	freopen("auxiliary.in", "r", stdin);
	freopen("auxiliary.out", "w", stdout); 
#endif
	int n;
	scanf("%d", &n);
	dp[0] = 0;
	for(int i = 1; i <= n; i++) 
		dp[i] = -1;

	for(int i = 1; i <= n; i++) {
		if(i >= 2 && dp[i - 2] != -1)
			dp[i] = max(dp[i], dp[i - 2] + 1);
		if(i >= 3 && dp[i - 3] != -1)
			dp[i] = max(dp[i], dp[i - 3] + 7);
		if(i >= 4 && dp[i - 4] != -1)
			dp[i] = max(dp[i], dp[i - 4] + 4);
		if(i >= 5 && dp[i - 5] != -1)
			dp[i] = max(dp[i], dp[i - 5] + 5);
		if(i >= 6 && dp[i - 6] != -1)
			dp[i] = max(dp[i], dp[i - 6] + 9);
		if(i >= 7 && dp[i - 7] != -1)
			dp[i] = max(dp[i], dp[i - 7] + 8);
	}
	printf("%d\n", dp[n]);
	return 0;
}
