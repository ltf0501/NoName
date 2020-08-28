#include <bits/stdc++.h>
using namespace std;
const int kN = 1e4 + 10;

int n;
int mxson[kN], sz[kN], p[kN];
int top[kN], in[kN], dfs_clock, dep[kN];
vector<int> g[kN];

void Dfs1(int u, int fa = -1, int d = 0) {
	sz[u] = 1, mxson[u] = -1, p[u] = fa, dep[u] = d;
	for(int v : g[u]) if(v != fa) {
		Dfs1(v, u, d + 1);
		sz[u] += sz[v];
		if(mxson[u] == -1 || sz[mxson[u]] < sz[v]) mxson[u] = v;
	}
}

void Dfs2(int u, int fa, int tp) {
	in[u] = ++dfs_clock, top[u] = tp;
	if(mxson[u] != -1) Dfs2(mxson[u], u, tp);
	for(int v : g[u]) 
		if(v != fa && v != mxson[u]) Dfs2(v, u, v);
}

#define lc (o << 1)
#define rc (o << 1 | 1)
int mx[kN << 2], cnt[kN << 2], tg[kN << 2];
void push_down(int o) {
	if(!tg[o]) return;
	mx[lc] += tg[o], mx[rc] += tg[o];
	tg[lc] += tg[o], tg[rc] += tg[o];
	tg[o] = 0;
}
void push_up(int o) {
	mx[o] = max(mx[lc], mx[rc]);
	if(mx[lc] > mx[rc]) cnt[o] = cnt[lc];
	else if(mx[lc] < mx[rc]) cnt[o] = cnt[rc];
	else cnt[o] = cnt[lc] + cnt[rc];
}
void Build(int l = 1, int r = n, int o = 1) {
	tg[o] = 0;
	if(l == r) {
		mx[o] = 0, cnt[o] = 1;
		return;
	}
	int m = (l + r) >> 1;
	Build(l, m, lc), Build(m + 1, r, rc);
	push_up(o);
}
void update(int ql, int qr, int k, int l = 1, int r = n, int o = 1) {
	if(ql <= l && r <= qr) {
		mx[o] += k, tg[o] += k;
		return;
	}
	int m = (l + r) >> 1;
	push_down(o);
	if(ql <= m) update(ql, qr, k, l, m, lc);
	if(qr > m) update(ql, qr, k, m + 1, r, rc);
	push_up(o);
}

void Add(int a, int b, int d) {
	while(top[a] != top[b]) {
		if(dep[top[a]] < dep[top[b]]) swap(a, b);
		//printf("up: %d %d\n", in[top[a]], in[a]);
		update(in[top[a]], in[a], d);
		a = p[top[a]];
	}
	if(in[a] > in[b]) swap(a, b);
	//printf("up: %d %d\n", in[a], in[b]);
	update(in[a], in[b], d);
}

void Init() {
	dfs_clock = 0;
	for(int i = 1; i <= n; i++) g[i].clear();
}
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%d", &n);
		Init();
		for(int i = 1; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}

		Dfs1(1);
		Dfs2(1, -1, 1);
		//printf("top: ");
		//for(int i = 1; i <= n; i++) printf("%d ", top[i]);
		//printf("in: ");
		//for(int i = 1; i <= n; i++) printf("%d ", in[i]);

		Build();
		//printf("init: mx = %d, cnt = %d\n", mx[1], cnt[1]);
		int q; scanf("%d", &q);
		printf("Case %d:\n", ++cas);
		while(q--) {
			int k; scanf("%d", &k);
			vector<int> a(k), b(k);
			for(int i = 0; i < k; i++) {
				scanf("%d%d", &a[i], &b[i]);
				Add(a[i], b[i], 1);
			}
			int ans = mx[1] == k ? cnt[1] : 0;
			//printf("mx = %d, cnt = %d\n", mx[1], cnt[1]);
			printf("%d\n", ans);
			for(int i = 0; i < k; i++) Add(a[i], b[i], -1);
		}
	} 
	return 0;
}

