#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
const ll INF = 1e16;
const int maxn = 1e5 + 10;
const int maxk = 1e2 + 10;
ll dp[maxn][maxk];
vector<pii> g[maxn];
int n, k;
 
void init(int n) {
	for(int i = 1; i <= n; i++) g[i].clear();
}
int dfs(int u, int fa, int w) {
	if(int(g[u].size()) == 1) {
		dp[u][1] = 1LL * (k - 1) * w;
		return 1;
	}
	int res = 0;
	for(auto s : g[u]) if(s.F != fa) {
		int v = s.F;
		int res_v =	dfs(v, u, s.S);
		res += res_v;
		for(int i = min(k, res); i >= 1; i--) {
			for(int j = 0; j <= min(i, res_v); j++) {
				dp[u][i] = min(dp[u][i], dp[v][j] + dp[u][i - j]);
			}
		}
	}
	for(int i = 1; i <= min(res, k); i++) {
		dp[u][i] += 1LL * i * (k - i) * w;
	}
	return res;
}
int main() {
	int T;
	scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%d%d", &n, &k);
		init(n);
		for(int i = 1; i < n; i++) {
			int x, y, d;
			scanf("%d%d%d", &x, &y, &d);
			g[x].push_back({y, d}), g[y].push_back({x, d});
		}
		printf("Case #%d: ", ++cas);
		int rt = -1;
		for(int i = 1; i <= n; i++) 
			if(int(g[i].size()) >= 2) {rt = i; break;}
 
		if(rt == -1) {
			if(k == 1) puts("0");
			else printf("%d\n", g[1][0].S);
			continue;
		} 
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= k; j++) dp[i][j] = INF;
		}
 
		int leaf = dfs(rt, 0, 0);
		printf("%lld\n", dp[rt][k]);
	}
	return 0;
}
