#include <bits/stdc++.h>
using namespace std;
const int kN = 1e3 + 10;
const long long kMod = 1LL << 32;
typedef pair<int, int> pii;
#define F first
#define S second

struct Edge {
	int x, y, w;
};
int n, m, k; 
vector<int> g[kN];
vector<Edge> edges;
int to(int x, int id) {return x ^ edges[id].x ^ edges[id].y;}

stack<pii> s;
int in[kN], dfs_clock;
int p[kN];
vector<vector<int>> vec;
void dfs(int u, int fa = -1) {
	in[u] = ++dfs_clock;
	for(int id : g[u]) {
		int v = to(u, id);
		if(v == fa) continue;
		if(!in[v]) p[v] = id, dfs(v, u);
		else if(in[v] > in[u]) {
			vector<int> tmp;
			tmp.push_back(edges[id].w);
			int y = v;
			while(y != u) {
				int ii = p[y];
				tmp.push_back(edges[ii].w);
				y = to(y, ii);
			}
			vec.push_back(tmp);
		}
	}
}

void init() {
	for(int i = 1; i <= n; i++) g[i].clear();
	edges.clear();
	vec.clear();
	dfs_clock = 0;
	for(int i = 1; i <= n; i++) in[i] = 0;	
}
int main() {
	int cas = 0;
	while(~scanf("%d%d", &n, &m)) {
		init();
		int sum = 0;
		for(int i = 0; i < m; i++) {
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			int sz = edges.size();
			g[x].push_back(sz), g[y].push_back(sz);
			edges.push_back({x, y, w});
			sum += w;
		}
		dfs(1);
		for(auto &v : vec) {
			sort(v.begin(), v.end(), greater<int>());
		} 

		scanf("%d", &k);
		printf("Case #%d: ", ++cas);
		if(vec.empty()) {
			printf("%d\n", sum);
			continue;
		}
		vector<int> now;
		for(int i = 0; i < min(k, int(vec[0].size())); i++) now.push_back(vec[0][i]);

		for(int i = 1; i < int(vec.size()); i++) {
			vector<int> nxt;
			int sz = vec[i].size();
			vector<int> cnt(sz);
			priority_queue<pii> pq;
			for(int j = 0; j < sz; j++) pq.emplace(now[0] + vec[i][j], j);
			while(!pq.empty() && nxt.size() < k) {
				pii p = pq.top(); pq.pop();
				nxt.push_back(p.F);
				int j = p.S;
				if(cnt[j] != now.size() - 1) pq.emplace(now[++cnt[j]] + vec[i][j], j);
			}
			now = nxt;
		}

		long long ans = 0;
		for(int i = 0; i < int(now.size()); i++) {
			ans = (ans + 1LL * (sum - now[i]) * (i + 1)) % kMod;
		}
		printf("%lld\n", ans);
	} 
	return 0;
}
