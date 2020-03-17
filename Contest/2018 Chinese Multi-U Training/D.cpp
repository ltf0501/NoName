#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

int n, q;
vector<int> g[kN];
int in[kN], out[kN], dfs_clock;
int dep[kN], anc[18][kN];

void pre_dfs(int u, int fa = 0, int d = 0) {
	in[u] = ++dfs_clock, dep[u] = d, anc[0][u] = fa;
	for(int v : g[u]) 
		if(v != fa) pre_dfs(v, u, d + 1);
	out[u] = dfs_clock;
}
bool ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}

int LCA(int x, int y) {
	if(ancestor(x, y)) return x;
	if(ancestor(y, x)) return y;
	for(int i = 17; i >= 0; i--)
		if(!ancestor(anc[i][x], y)) x = anc[i][x];
	return anc[0][x];
}
int Dis(int x, int y) {return dep[x] + dep[y] - 2 * dep[LCA(x, y)];}
int Midpoint(int x, int y) {
	if(x == y) return x;
	if(dep[x] < dep[y]) swap(x, y);
	int tot = Dis(x, y) >> 1;
	for(int i = 17; i >= 0; i--)
		if(tot & (1 << i)) x = anc[i][x];
	return x;
}

int d[kN], cen_fa[kN];
int cdep[kN], cdis[19][kN];
bool vis[kN];
vector<int> dis[kN], dis_fa[kN];
vector<int> now;
int sz[kN], mx[kN];
void get_cen(int u) {
	vis[u] = 1, sz[u] = 1, mx[u] = 0;
	now.push_back(u);
	for(int v : g[u]) if(!vis[v]) {
		get_cen(v);
		sz[u] += sz[v], mx[u] = max(mx[u], sz[v]);
	}
}
void get_dis(int u, int dd, int step, int cen) {
	vis[u] = 1, cdis[step][u] = dd;
	if(u <= n) {
		dis[cen].push_back(dd);
		if(step) dis_fa[cen].push_back(cdis[step - 1][u]);
	}
	now.push_back(u);
	for(int v : g[u]) if(!vis[v]) {
		get_dis(v, dd + 1, step, cen);
	}
}
void dfs(int u, int fa = 0, int step = 0) {
	int cen = -1;
	get_cen(u);
	int s = now.size();
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
		vis[w] = 0;
	}
	now.clear();
	cen_fa[cen] = fa, cdep[cen] = step;

	get_dis(cen, 0, step, cen);
	for(int w : now) vis[w] = 0;
	now.clear();

	vis[cen] = 1;
	for(int v : g[cen]) 
		if(!vis[v]) dfs(v, cen, step + 1);
}

int query(int x, int w) {
	int res = 0;
	int cur = x;
	for(int i = cdep[x]; i >= 0; i--, cur = cen_fa[cur]) {
		res += upper_bound(dis[cur].begin(), dis[cur].end(), w - cdis[i][x]) - dis[cur].begin();
		if(i > 0) res -= upper_bound(dis_fa[cur].begin(), dis_fa[cur].end(), w - cdis[i - 1][x]) - dis_fa[cur].begin();
	}
	return res;
}
void init() {
	for(int i = 1; i <= n * 2 - 1; i++) g[i].clear();
	dfs_clock = 0;
	for(int i = 1; i <= n * 2 - 1; i++) dis[i].clear(), dis_fa[i].clear();
	now.clear();
	for(int i = 1; i <= n * 2 - 1; i++) vis[i] = 0;
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
		n = rit(), q = rit();
		init();
		int cur = n;
		for(int i = 1, x, y; i < n; i++) {
			x = rit(), y = rit();
			++cur;
			g[x].push_back(cur), g[y].push_back(cur);
			g[cur].push_back(x), g[cur].push_back(y);
		}
		pre_dfs(1); out[0] = dfs_clock;
		for(int j = 1; j <= 17; j++)
			for(int i = 1; i <= cur; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];

		dfs(1);
		for(int i = 1; i <= 2 * n - 1; i++) {
			sort(dis[i].begin(), dis[i].end());
			sort(dis_fa[i].begin(), dis_fa[i].end());
		}
		int ans = 0;
		while(q--) {
			int u, v, w; u = rit(), v = rit(), w = rit(); 
			u = (u + ans) % n + 1, v = (v + ans) % n + 1, w = (w + ans) % n;
			int num_u = query(u, 2 * w), num_v = query(v, 2 * w);
			int k = Dis(u, v) / 2;
			if(k <= 2 * w) {
				int z = Midpoint(u, v);
				int num_z = query(z, 2 * w - k);
				ans = num_u + num_v - num_z;
			}
			else ans = num_u + num_v;
			printf("%d\n", ans);
		}
	}
	return 0;
} 
