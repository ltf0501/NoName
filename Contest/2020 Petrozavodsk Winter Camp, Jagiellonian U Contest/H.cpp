#include <bits/stdc++.h>
using namespace std;
const int kN = 305;

int n;
int x[kN], y[kN];
bool g[kN][kN], vis[kN][kN][2];
double dp[kN][kN][2];

double dis(int i, int j) {return sqrt(1LL * (x[i] - x[j]) * (x[i] - x[j]) + 1LL * (y[i] - y[j]) * (y[i] - y[j]));}

double Dp(int i, int j, bool dir) { // now on j before i, dir
	if(vis[i][j][dir]) return dp[i][j][dir];
	vis[i][j][dir] = 1;
	double res = 0;
	if(!dir) {
		for(int k = (i + 1); k < (j > i ? j : j + n); k++)
			if(g[j][k % n]) res = max(res, dis(j, k % n) + max(Dp(j, k % n, 1), Dp(i, k % n, 0)));
	}
	else {
		for(int k = (j + 1); k < (i > j ? i : i + n); k++)
			if(g[j][k % n]) res = max(res, dis(j, k % n) + max(Dp(j, k % n, 0), Dp(i, k % n, 1)));
	}
	//printf("dp(%d, %d, %d) = %.3f\n", i, j, dir, res);
	return dp[i][j][dir] = res;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		memset(g, 0, sizeof(g));
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);	
		int m; scanf("%d", &m);
		for(int i = 0; i < m; i++) {
			int a, b; scanf("%d%d", &a, &b);
			a--, b--;
			g[a][b] = g[b][a] = 1;
		}
		
		double ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) if(g[i][j]) {
				//printf("dis(%d, %d) = %.3f\n", i, j, dis(i, j));
				ans = max(ans, dis(i, j) + max({Dp(i, j, 0), Dp(i, j, 1), Dp(j, i, 0), Dp(j, i, 1)}));
			}
		}
		printf("%.9f\n", ans);
	}
	return 0;
}	
