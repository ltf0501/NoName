#include <bits/stdc++.h>
using namespace std;
const int kN = 1.5e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second
pii a[kN];
int dp[kN][15];
bool vis[kN][15];
int n, k;
int dfs(int i, int k) {
	if(vis[i][k] == 1) return dp[i][k];
	if(i == n + 1) return 0;
	vis[i][k] = 1;
	int res;
	if(k > 0) res = min(a[i].F - a[i].S, dfs(i + 1, k - 1) - a[i].S);
	else res = a[i].F - a[i].S;
	res = max(res, dfs(i + 1, k));
	return dp[i][k] = res;
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].F, &a[i].S);
		sort(a + 1, a + n + 1);
		memset(vis, 0, sizeof(vis));
		printf("%d\n", dfs(1, k));
	}
}
