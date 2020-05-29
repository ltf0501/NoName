#include <bits/stdc++.h>
using namespace std; 
const int kN = 1e3 + 10;
const int kMod = 1e9 + 7;
int n, k;
vector<int> g[kN];
int sz[kN];
int dp[kN][kN][2];
int pre[kN][2], now[kN][2];
void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
void dfs(int u, int fa = 0) {
	sz[u] = 1;
	for(int v : g[u])
		if(v != fa) dfs(v, u);
	for(int i = 0; i <= 1; i++) for(int j = 0; j < 2; j++) pre[i][j] = 0;
	pre[0][0] = 1;
	for(int v : g[u]) if(v != fa) {
		for(int i = 0; i <= sz[u] + sz[v]; i++) for(int j = 0; j < 2; j++) now[i][j] = 0;
		//printf("cur = %d, sub: v = %d\n", u, v);
		for(int i = 0; i <= sz[u]; i++) for(int a = 0; a < 2; a++) if(pre[i][a]) {
			for(int j = 0; j <= sz[v]; j++) for(int b = 0; b < 2; b++) {
				add(now[i + j][a || b], 1LL * dp[v][j][b] * pre[i][a] % kMod);
			}
		}

		sz[u] += sz[v];
		for(int i = 0; i <= sz[u]; i++)
			for(int j = 0; j < 2; j++) pre[i][j] = now[i][j];
		//for(int i = 0; i <= sz[u]; i++) {
		//	for(int j = 0; j < 2; j++) printf("%d ", now[i][j]); puts("");
		//}
	}
	for(int i = 0; i <= sz[u]; i++) {
		for(int j = 0; j < 2; j++) for(int a = 0; a < 2; a++) {
			add(dp[u][i + (j && !a)][j], pre[i][a]);
		}
	} 
	//printf("dp[%d]:\n", u);
	//for(int i = 0; i <= sz[u]; i++) {
	//	for(int j = 0; j < 2; j++) printf("%d ", dp[u][i][j]); puts("");
	//}
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}

	dfs(1);
	printf("%d\n", dp[1][k][1]);
	return 0;
}
