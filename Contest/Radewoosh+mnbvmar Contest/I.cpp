#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second

int n;
vector<int> g[kN];

vector<int> dd[kN], fa_dd[kN];
bool vis[kN];
vector<int> now;
int sz[kN], mx[kN];
int cen_anc[20][kN], cen_dep[kN];
int dis[20][kN];

void GetCen(int u) {
	vis[u] = 1;
	now.push_back(u);
	sz[u] = 1, mx[u] = 0;
	for(int v : g[u]) if(!vis[v]) {
		GetCen(v);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]); 
	}
}
void GetDis(int u, int dep, int d) {
	vis[u] = 1;
	now.push_back(u);
	dis[dep][u] = d;	
	for(int v : g[u]) if(!vis[v]) {
		GetDis(v, dep, d + 1);
	}
}
void Dfs(int u, int dep = 0) {
	now.clear();
	int cen = -1;
	GetCen(u);
	int s = now.size();
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
		vis[w] = 0;
	}
	cen_dep[cen] = dep;
	now.clear();
	GetDis(cen, dep, 0);
	for(int w : now) {
		if(w <= n) dd[cen].push_back(dis[dep][w]);
		vis[w] = 0;
		cen_anc[dep][w] = cen;
	}
	sort(dd[cen].begin(), dd[cen].end()); 
	if(dep) {
		for(int w : now) {
			if(w <= n) fa_dd[cen].push_back(dis[dep - 1][w]); 
		}
		sort(fa_dd[cen].begin(), fa_dd[cen].end());
	}
	now.clear();

	vis[cen] = 1;
	for(int v : g[cen])
		if(!vis[v]) Dfs(v, dep + 1);
}

int in[kN], out[kN], dfs_clock;
int dep[kN], anc[20][kN];

void Dfs2(int u, int fa = 0, int d = 0) {
	in[u] = ++dfs_clock;
	anc[0][u] = fa;
	dep[u] = d;
	for(int v : g[u]) if(v != fa) {
		Dfs2(v, u, d + 1);
	}
	out[u] = dfs_clock;
}
int ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
int LCA(int x, int y) {
	if(ancestor(x, y)) return x;
	if(ancestor(y, x)) return y;
	for(int i = 19; i >= 0; i--)
		if(!ancestor(anc[i][x], y)) x = anc[i][x];
	return anc[0][x];
}
int Dis(int x, int y) {return dep[x] + dep[y] - 2 * dep[LCA(x, y)];}
int Climb(int x, int y, int d) {
	int l = LCA(x, y);
	if(dep[x] - dep[l] < d) {
		swap(x, y);
		d = Dis(x, y) - d;
	}

	for(int i = 19; i >= 0; i--)
		if(d & (1 << i)) x = anc[i][x];
	return x;
}

int Query(pii p) {
	int x = p.F, k = p.S;
	if(!x) return 0;
	int res = upper_bound(dd[x].begin(), dd[x].end(), k) - dd[x].begin();
	for(int i = cen_dep[x] - 1; i >= 0; i--) {
		int fa = cen_anc[i][x], cur = cen_anc[i + 1][x];
		int d = dis[i][x];
		res += upper_bound(dd[fa].begin(), dd[fa].end(), k - d) - dd[fa].begin();
		res -= upper_bound(fa_dd[cur].begin(), fa_dd[cur].end(), k - d) - fa_dd[cur].begin();
	}
	return res;
}
pii check(pii a, pii b) {
	if(a.F == 0 || b.F == 0) return {0, -1};
	
	int dis = Dis(a.F, b.F);
	if(a.S + b.S < dis) return {0, -1};
	if(a.S >= b.S + dis) return b;
	if(b.S >= a.S + dis) return a;
	return {Climb(a.F, b.F, (a.S - b.S + dis) / 2), (a.S + b.S - dis) / 2};
}
int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(n + i), g[y].push_back(n + i);
		g[n + i].push_back(x), g[n + i].push_back(y);
	} 

	Dfs(1);
	Dfs2(1); out[0] = dfs_clock;
	for(int j = 1; j < 20; j++)
		for(int i = 1; i < 2 * n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];

	int q;
	scanf("%d", &q);
	while(q--) {
		int k; scanf("%d", &k);
		vector<pii> p(k);
		for(int i = 0; i < k; i++) {
			scanf("%d%d", &p[i].F, &p[i].S);
			p[i].S <<= 1;
		}

		vector<pii> pre(k), suf(k);	
		pre[0] = p[0];
		for(int i = 1; i < k; i++) pre[i] = check(pre[i - 1], p[i]);
		suf[k - 1] = p[k - 1];
		for(int i = k - 2; i >= 0; i--) suf[i] = check(suf[i + 1], p[i]);

		long long ans = 0;
		for(int i = 0; i < k; i++) {
			pii tmp;
			if(i == 0) tmp = suf[1];
			else if(i == k - 1) tmp = pre[k - 2];
			else tmp = check(pre[i - 1], suf[i + 1]);
			ans += Query(tmp);
		}
		ans -= 1LL * Query(pre[k - 1]) * (k - 1);
		printf("%lld\n", ans);
	}
	return 0;
}
