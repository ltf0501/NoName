#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;

int n, m, C, cen;
vector<int> g[kN];
bool check[kN];

int in[kN], dfs_clock;
int scc_cnt, sccno[kN];
vector<int> scc[kN];
bool vis[kN], dp[kN];
stack<int> s;

vector<int> scc_g[kN];
int dfs(int u) {
	int lowu = in[u] = ++dfs_clock;
	s.push(u);
	for(int v : g[u]) {
		if(!in[v]) lowu = min(lowu, dfs(v));
		else if(!sccno[v]) lowu = min(lowu, in[v]);
	}
	if(lowu == in[u]) {
		scc_cnt++;
		while(true) {
			int x = s.top(); s.pop();
			sccno[x] = scc_cnt;
			scc[scc_cnt].push_back(x);
			if(x == u) break;
		}	
	}
	return lowu;
}

int dfs2(int u) {
	if(vis[u]) return dp[u];
	vis[u] = 1;
	if(u == cen) return dp[u] = 1;
	int res = 0;
	for(int v : scc_g[u])
		res |= dfs2(v);
	return dp[u] = res;
}
int main() {
	scanf("%d%d%d", &n, &m, &C);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		if(x != C) g[x].push_back(y);
		if(y == C) check[x] = 1;
	}
	for(int i = 0; i < n; i++)
		if(!in[i]) dfs(i); 
	cen = sccno[C];

	for(int i = 0; i < n; i++) {
		for(int v : g[i]) if(sccno[v] != sccno[i])
			scc_g[sccno[i]].push_back(sccno[v]);
	}
	//printf("sccno: ");
	//for(int i = 0; i < n; i++) printf("%d ", sccno[i]); puts("");
	//for(int i = 1; i <= scc_cnt; i++) {
	//	printf("scc[%d]: ", i);
	//	for(int x : scc[i]) printf("%d ", x); puts("");
	//}

  
	for(int i = 1; i <= scc_cnt; i++)
		if(!vis[i]) dfs2(i);
	//for(int i = 1; i <= scc_cnt; i++) printf("%d ", dp[i]); puts("");

	vector<int> ans;
	for(int i = 1; i <= scc_cnt; i++) {
		int cnt = 0;
		bool flag = 1;
		//printf("scc_g[%d]: ", i);
		//for(int v : scc_g[i]) printf("%d ", v); puts("");
		for(int v : scc_g[i]) if(dp[v]) {
			if(v != cen) flag = 0;
			else cnt++;
		}
		if(cnt == 1 && flag) {
			for(int x : scc[i])
				if(check[x]) ans.push_back(x);
		}
	}
	printf("%d\n", int(ans.size()));
	sort(ans.begin(), ans.end());
	for(int x : ans) printf("%d\n", x); puts("");
	return 0;
} 
