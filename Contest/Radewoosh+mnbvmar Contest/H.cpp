#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
typedef pair<__float128, int> pii;
#define F first
#define S second

vector<int> g[kN];
__float128 dp[kN];
bool vis[kN];

__float128 sum[kN], mn[kN];
int cnt[kN];
bool possible[kN];
int n, m; int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0., n);
	for(int i = 1; i <= n; i++) possible[i] = true;
	while(!pq.empty()) {
		auto p = pq.top(); pq.pop();
		__float128 val = p.F;
		int u = p.S;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int v : g[u]) if(!vis[v]) {
			if(dp[v] == 0) {
				dp[v] = 1.5 + val;
				mn[v] = 2.0 + val;
				sum[v] = 1.0 + 0.75 * val;
				pq.emplace(dp[v], v);
			}
			else if(possible[v]) { 
				sum[v] += pow(0.25, cnt[v]) * (1.0 + 0.75 * val);
				__float128 tmp = sum[v] + pow(0.25, cnt[v] + 1) * mn[v];
				//printf("v = %d, cnt = %d, tmp = %f\n", v, cnt[v], tmp); 
				if(dp[v] > sum[v] + pow(0.25, cnt[v] + 1) * mn[v]) {
					dp[v] = sum[v] + pow(0.25, cnt[v] + 1) * mn[v];
					pq.emplace(dp[v], v);
				}
				else {
					possible[v] = false;
				}
			}
			cnt[v]++;
		}
	}
	printf("%.12f\n", (double) dp[1]);
	return 0;
} 
