#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define F first
#define S second
const int maxn = 5e4 + 10;
const int maxp = 5e6 + 10;
const int MAX = 100000;
struct node {
	static node p[maxp];
	node *l, *r;
	int num;
	node(int val = 0): l(nullptr), r(nullptr), num(val) {}
	void pull() {
		num = 0;
		if(l) num += l->num;
		if(r) num += r->num;
	}
}node::p[maxp], *ptr = node::p;
inline int sz(node *o) {return o ? o->num : 0;}
node *build(int l, int r) {
	node *u = new(ptr++) node();
	if(l == r) return u;
	int m = (l + r) >> 1;
	u->l = build(l, m), u->r = build(m + 1, r);
	return u;
}
node *update(int x, node *o, int l, int r) {
	if(!x) return o;
	if(l == r) return new(ptr++) node(o->num + 1); 
	int m = (l + r) >> 1;
	node *v = new(ptr++) node();
	if(x <= m) {
		v->l = update(x, o->l, l, m);
		v->r = o->r;
	}
	else {
		v->l = o->l;
		v->r = update(x, o->r, m + 1, r);
	}
	v->pull();
	return v;
}
int query(node *a, node *b, node *c, int l, int r, int k) {
	if(l == r) return l;
	int m = (l + r) >> 1;
	int cnt = sz(a->l) + sz(b->l) - 2 * sz(c->l); 
	if(cnt >= k) return query(a->l, b->l, c->l, l, m, k);
	else return query(a->r, b->r, c->r, m + 1, r, k - cnt);
}
vector<pii> g[maxn];
int in[maxn], out[maxn], dfs_clock;
int dep[maxn];
int anc[18][maxn];
node *rt[maxn];
void dfs(int u, int fa, int dis, int d) {
	in[u] = ++dfs_clock;
	anc[0][u] = fa;
	dep[u] = d;
	rt[u] = update(dis, rt[fa], 1, MAX);
	for(pii v : g[u]) if(v.F != fa) {
		dfs(v.F, u, v.S, d + 1);
	}
	out[u] = dfs_clock; 
}
bool ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
int LCA(int x, int y) {
	if(ancestor(x, y)) return x;
	if(ancestor(y, x)) return y;
	for(int i = 17; i >= 0; i--) if(!ancestor(anc[i][x], y))
		x = anc[i][x];
	return anc[0][x];
}
int dist(int x, int y) {return dep[x] + dep[y] - 2 * dep[LCA(x, y)];} 
void init(int n) {
	ptr = node::p;
	for(int i = 1; i <= n; i++) g[i].clear();
	dfs_clock = 0; 
}
int main() { 
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		init(n);
		for(int i = 1; i < n; i++) {
			int x, y, d;
			scanf("%d%d%d", &x, &y, &d);
			g[x].emplace_back(y, d), g[y].emplace_back(x, d);
		}
		rt[0] = build(1, MAX);
		dfs(1, 0, 0, 0); out[0] = dfs_clock;
		for(int j = 1; j <= 17; j++) 
			for(int i = 1; i <= n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];
		int q;
		scanf("%d", &q);
		while(q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			int num = dist(x, y);
			if(num & 1) {
				int a = query(rt[x], rt[y], rt[LCA(x, y)], 1, MAX, (num >> 1) + 1);
				printf("%d.0\n", a);
			}
			else {
				int a = query(rt[x], rt[y], rt[LCA(x, y)], 1, MAX, (num >> 1));
				int b = query(rt[x], rt[y], rt[LCA(x, y)], 1, MAX, (num >> 1) + 1);
				int k = a + b;
				if(k & 1) printf("%d.5\n", k >> 1);
				else printf("%d.0\n", k >> 1); 
			}
		}
	}
	return 0;
}
