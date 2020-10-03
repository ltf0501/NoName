#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second

void Bye() {
	puts("No");
	exit(0);
}
int n, q;
vector<int> g[kN];
int sz[kN], mxson[kN];
int top[kN], dep[kN], p[kN];
int dfs_clock, in[kN], out[kN];
int anc[20][kN];

void Dfs1(int u, int fa = 0, int d = 0) {
	sz[u] = 1, dep[u] = d, p[u] = fa;
	for(int v : g[u]) if(v != fa) {
		Dfs1(v, u, d + 1);
		sz[u] += sz[v];
		if(sz[v] > sz[mxson[u]]) mxson[u] = v;
	} 
}

void Dfs2(int u, int fa = 0, int tp = 1) {
	in[u] = ++dfs_clock, top[u] = tp;
	if(mxson[u]) Dfs2(mxson[u], u, tp);
	for(int v : g[u]) if(v != fa && v != mxson[u]) {
		Dfs2(v, u, v);
	}
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
int Len(int a, int b) {return dep[a] + dep[b] - 2 * dep[LCA(a, b)];}

#define lc (o << 1)
#define rc (o << 1 | 1)
int mn[kN << 2], mx[kN << 2], tg[kN << 2];
void push_up(int o) {
	mx[o] = max(mx[lc], mx[rc]);
	mn[o] = min(mn[lc], mn[rc]);
}
void push_down(int o) {
	if(!tg[o]) return;
	mn[lc] = mn[rc] = tg[o];
	mx[lc] = mx[rc] = tg[o];
	tg[lc] = tg[rc] = tg[o];
	tg[o] = 0;
}
void update(int ql, int qr, int k, int l = 1, int r = n, int o = 1) {
	//printf("ql = %d, qr = %d, k = %d, l = %d, r = %d\n", ql, qr, k, l, r);
	if(ql <= l && r <= qr) {
		mn[o] = mx[o] = tg[o] = k;
		return;
	}
	push_down(o);
	int m = (l + r) >> 1;
	if(ql <= m) update(ql, qr, k, l, m, lc);
	if(qr > m) update(ql, qr, k, m + 1, r, rc);
	push_up(o);
}
pii query(int ql, int qr, int l = 1, int r = n, int o = 1) {
//	if(cnt < 10) printf("ql = %d, qr = %d, l = %d, r = %d\n", ql, qr, l, r);
	if(ql <= l && r <= qr) {
		return make_pair(mn[o], mx[o]);
	}
	push_down(o);
	int m = (l + r) >> 1;
	if(qr <= m) return query(ql, qr, l, m, lc);
	if(ql > m) return query(ql, qr, m + 1, r, rc);
	pii res1 = query(ql, qr, l, m, lc);
	pii res2 = query(ql, qr, m + 1, r, rc);
	return make_pair(min(res1.F, res2.F), max(res1.S, res2.S));
}
pii Query(int a, int b) {
	//printf("a = %d, b = %d\n", a, b);
	int Mn = -1, Mx = -1;
	while(top[a] != top[b]) {
		if(dep[top[a]] < dep[top[b]]) swap(a, b);
		auto res = query(in[top[a]], in[a]);
		//printf("top = %d, a = %d, mn = %d, mx = %d\n", top[a], a, res.F, res.S);
		if(res.F != res.S) Bye();	
		if(Mn != -1 && res.F != Mn) Bye();
		if(Mn == -1) tie(Mn, Mx) = res; 
		a = p[top[a]];
	} 
	if(in[a] > in[b]) swap(a, b);
	auto res = query(in[a], in[b]);
	//printf("top = %d, a = %d, mn = %d, mx = %d\n", a, b, res.F, res.S);
	if(res.F != res.S) Bye();	
	if(Mn != -1 && res.F != Mn) Bye();
	if(Mn == -1) tie(Mn, Mx) = res; 
	//printf("Mn = %d, Mx = %d\n", Mn, Mx);
	return make_pair(Mn, Mx);
}

void Insert(int a, int b, int timer) {
	while(top[a] != top[b]) {
		if(dep[top[a]] < dep[top[b]]) swap(a, b);
		update(in[top[a]], in[a], timer);
		a = p[top[a]];
	} 
	if(in[a] > in[b]) swap(a, b);
	update(in[a], in[b], timer);
}
int id[kN];
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n - 1; i++) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	Dfs1(1); 
	Dfs2(1); out[0] = dfs_clock;
	for(int j = 1; j <= 17; j++)
		for(int i = 1; i <= n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];
	vector<pii> edges(q + 1);
	vector<int> len(q + 1);
	for(int i = 1; i <= q; i++) id[i] = i;

	for(int i = 1; i <= q; i++) {
		scanf("%d%d", &edges[i].F, &edges[i].S);
		len[i] = Len(edges[i].F, edges[i].S);
	}
	sort(id + 1, id + q + 1, [&](int i, int j) {
			return len[i] > len[j];
			});

	for(int i = 1; i <= q; i++) {
		int ii = id[i];
		auto res = Query(edges[ii].F, edges[ii].S);
		Insert(edges[ii].F, edges[ii].S, i);
	}
	puts("Yes");
	return 0;
} 
