#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

struct Edge {
	int x, y, w;
};

bool vis[kN];
int main() {
	int n; scanf("%d", &n);
	map<int, vector<int>> mp;
	vector<vector<int>> g(n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		while(x--) {
			int k; scanf("%d", &k);
			g[i].push_back(k);
			mp[k].push_back(i);
		}
	}

	vector<Edge> ans;
	vis[0] = 1;
	queue<int> q; q.push(0);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 1;

		for(int i : g[u]) {
			for(int v : mp[i]) {
				if(!vis[v]) {
					vis[v] = 1; q.push(v);
					ans.push_back({u, v, i});
				}
			}
			mp[i].clear();
		}
	}
	
	bool flag = 1;
	for(int i = 0; i < n; i++) flag &= vis[i];
	if(!flag) {
		puts("impossible");
	}
	else {
		for(auto e : ans) printf("%d %d %d\n", e.x + 1, e.y + 1, e.w);
	}
	return 0;
}
