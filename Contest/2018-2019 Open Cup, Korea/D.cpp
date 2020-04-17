#include <bits/stdc++.h>
using namespace std;
const int kN = 3e5 + 10;

int n, m;
bool vis[kN];
int l[kN], r[kN], deg[kN], ans[kN];
vector<int> g[kN];

struct P {
	int l, r, id;
	bool operator < (const P& t) const {
		return l > t.l;
	}
};

int dfs(int x) {
	if(vis[x]) return r[x];
	vis[x] = 1;
	for(int v : g[x]) r[x] = min(r[x], dfs(v) - 1);
	return r[x];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]);
	for(int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		deg[y]++;
	}
	priority_queue<P> ok;
	priority_queue<pair<int, int>> pq;

	for(int i = 1; i <= n; i++) {
		r[i] = dfs(i);
		if(!deg[i]) ok.push({l[i], r[i], i});
	}

	for(int i = 1; i <= n; i++) {
		while(!ok.empty() && ok.top().l <= i) {
			auto p = ok.top(); ok.pop();
			pq.emplace(-p.r, p.id);
		}

		if(pq.empty()) return puts("-1"), 0;

		int x = pq.top().second; pq.pop();
		if(r[x] < i) return puts("-1"), 0;
		ans[i] = x;
		for(int v : g[x])
			if(!(--deg[v])) ok.push({l[v], r[v], v});
	}

	for(int i = 1; i <= n; i++) printf("%d ", ans[i]); puts("");
	return 0;
}
