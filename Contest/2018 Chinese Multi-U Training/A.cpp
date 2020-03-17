#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const int kM = 2e5 + 10;
struct Edge {
	int x, y, w;
	bool operator < (const Edge &r) const {
		return w > r.w;
	}
};
int n, m; 
uint64_t ans;
vector<Edge> edges;
bool used[kM];
vector<int> g[kN];
int to(int x, int id) {return x ^ edges[id].x ^ edges[id].y;}
int p[kN], sz[kN];
int cnt[35][kN];

int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}
bool Union(int x, int y, int w, bool flag) {
	x = find(x); y = find(y);
	if(x == y) return 0;
	if(sz[x] < sz[y]) swap(x, y);
	if(flag) {
		uint64_t tmp = 0;
		for(int i = 0; i < 31; i++) {
			bool ok = w & (1 << i);
			if(!ok) tmp += (1ULL << i) * (1LL * cnt[i][x] * (sz[y] - cnt[i][y]) + 1LL * cnt[i][y] * (sz[x] - cnt[i][x]));
			else tmp += (1ULL << i) * (1LL * cnt[i][x] * cnt[i][y] + 1LL * (sz[x] - cnt[i][x]) * (sz[y] - cnt[i][y]));
		}
		ans += tmp;
		for(int i = 0; i < 31; i++) cnt[i][x] += cnt[i][y];
	}
	sz[x] += sz[y], p[y] = x;
	return 1;
}
int fa[kN];
int in[kN], out[kN], dfs_clock;
void dfs(int u, int fa_id = -1) {
	in[u] = ++dfs_clock;
	fa[u] = fa_id;
	for(int i : g[u]) if(i != fa_id) {
		int v = to(u, i);
		dfs(v, i);
	}
	out[u] = dfs_clock;
}
bool ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
void update(int x, int y, int w) {
	if(ancestor(y, x)) swap(x, y);
	while(!ancestor(x, y)) {
		edges[fa[x]].w += w;
		x = to(x, fa[x]);
	}
	while(!ancestor(y, x)) {
		edges[fa[y]].w += w;
		y = to(y, fa[y]);
	}
}

void init() {
	edges.clear();
	for(int i = 1; i <= n; i++) g[i].clear();
	dfs_clock = 0;
	for(int i = 0; i < m; i++) used[i] = 0;
	ans = 0;
}
int rit() {
	int res = 0;
	char c;
	while(c = getchar(), !isdigit(c));
	res = c - '0';
	while(c = getchar(), isdigit(c)) res = res * 10 + (c - '0');
	return res;
}
int main() {
	int T; T = rit(); 
	while(T--) {
		n = rit(), m = rit();
		init();
		for(int i = 0, x, y, w; i < m; i++) {
			x = rit(), y = rit(), w = rit();
			edges.push_back({x, y, w});
		}
		sort(edges.begin(), edges.end());
		//for(auto e : edges) printf("%d %d %d\n", e.x, e.y, e.w);
		for(int i = 1; i <= n; i++) sz[i] = 1, p[i] = i;
		for(int i = 0; i < m; i++) {
			int x = edges[i].x, y = edges[i].y;
			if(Union(x, y, 0, 0)) {
				used[i] = 1;
				g[x].push_back(i), g[y].push_back(i);
			}
		}
		dfs(1); out[0] = dfs_clock;
		for(int i = 0; i < m; i++)
			if(!used[i]) update(edges[i].x, edges[i].y, edges[i].w);

		for(int i = 1; i <= n; i++) {
			sz[i] = 1, p[i] = i;
			for(int j = 0; j < 31; j++) {
				if(i & (1 << j)) cnt[j][i] = 1;
				else cnt[j][i] = 0;
			}
		}
		vector<int> r(m);
		for(int i = 0; i < m; i++) r[i] = i;
		sort(r.begin(), r.end(), [&](int i, int j) {return edges[i].w > edges[j].w;});
		for(int i = 0; i < m; i++)
			if(used[r[i]]) Union(edges[r[i]].x, edges[r[i]].y, edges[r[i]].w, 1);
		printf("%llu\n", (unsigned long long)ans);
	}
	return 0;
}
