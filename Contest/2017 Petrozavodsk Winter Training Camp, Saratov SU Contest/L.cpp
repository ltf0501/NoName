#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

struct DominatorTree {
	int n;
	vector<int> g[kN], rev_g[kN];	
	int p[kN], in[kN], id[kN], dfs_clock;
	int sdom[kN], idom[kN], best[kN];
	vector<int> tree[kN];
	
	int sz[kN];

	void init(int _n) {
		n = _n;
		for(int i = 1; i <= n; i++) g[i].clear(), rev_g[i].clear();
	}

	void AddEdge(int u, int v) {
		g[u].push_back(v);
		rev_g[v].push_back(u);
	}

	void dfs(int u) {
		id[in[u] = ++dfs_clock] = u;
		for(int v : g[u]) if(!in[v]) {
			dfs(v), p[in[v]] = in[u];
		}
	}

	int find(int y, int x) {
		if(y <= x) return y;
		int tmp = find(p[y], x);
		if(sdom[best[y]] > sdom[best[p[y]]]) best[y] = best[p[y]];
		return p[y] = tmp;
	}

	void dfs2(int u) {
		sz[u] = 1;
		for(int v : tree[u])
			dfs2(v), sz[u] += sz[v];
	}

	void Tarjan(int root) {
		dfs_clock = 0;
		for(int i = 1; i <= n; i++) {
			in[i] = idom[i] = 0;
			tree[i].clear();
			best[i] = sdom[i] = i;
		}
		dfs(root);
		for(int i = n; i > 1; i--) {
			int u = id[i];
			for(int v : rev_g[u]) {
				v = in[v];
				if(!v) continue;
				find(v, i);
				sdom[i] = min(sdom[i], sdom[best[v]]);
			}
			if(i != 1) tree[sdom[i]].push_back(i);
			for(int v : tree[p[i]]) {
				find(v, p[i]);
				idom[v] = sdom[best[v]] == p[i] ? p[i] : best[v];
			}
			tree[p[i]].clear();
		}

		for(int i = 2; i <= dfs_clock; i++) {
			if(idom[i] != sdom[i]) idom[i] = idom[idom[i]];
			tree[id[idom[i]]].push_back(id[i]);
		} 

		//puts("g:");
		//for(int i = 1; i <= n; i++) {
		//	printf("%d: ", i);
		//	for(int x : g[i]) printf("%d ", x); puts("");
		//}

		//puts("tree:");
		//for(int i = 1; i <= n; i++) {
		//	printf("%d: ", i);
		//	for(int x : tree[i]) printf("%d ", x); puts("");
		//}

		dfs2(root); 
	}

	int Size(int u) {
		return sz[u];
	}
} dt;

const long long kInf = 1e16;
typedef pair<long long, int> pii;
#define F first
#define S second
int n, m;
struct Edge {
	int x, y, w;
};
vector<Edge> edges;
int to(int x, int id) {return x ^ edges[id].x ^ edges[id].y;}
vector<int> g[kN], pre[kN], g2[kN];
bool vis[kN];
long long dis[kN];
int deg[kN], anc[kN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		g[x].push_back(i), g[y].push_back(i);
		edges.push_back({x, y, w});
	}

	for(int i = 1; i <= n; i++) dis[i] = kInf;
	dis[1] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, 1);
	while(!pq.empty()) {
		auto p = pq.top(); pq.pop();
		if(vis[p.S]) continue;
		vis[p.S] = 1;
		for(int id : g[p.S]) {
			int v = to(p.S, id);
			if(dis[v] > p.F + edges[id].w) {
				dis[v] = p.F + edges[id].w;
				pq.emplace(dis[v], v);
				pre[v].clear();
				pre[v].push_back(id);
			}
			else if(dis[v] == p.F + edges[id].w) {
				pre[v].push_back(id);
			}
		}
	}

	dt.init(n);	
	for(int v = 1; v <= n; v++) {
		for(int id : pre[v]) {
			int u = to(v, id);
			dt.AddEdge(u, v);
			deg[v]++;
			anc[id] = u;
		}
	}
	dt.Tarjan(1);

	for(int i = 0; i < m; i++) {
		if(anc[i] == 0) {
			puts("0");
			continue;
		}
		int u = anc[i], v = to(u, i);
		
		if(deg[v] > 1) puts("0");
		else printf("%d\n", dt.Size(v));			
	}
	return 0;
}
