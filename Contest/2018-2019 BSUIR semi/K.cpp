#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
const int kMod = 1e9 + 7;

typedef pair<int, int> pii;
#define F first
#define S second

int n, q;
vector<pii> g[kN];
int p[kN];
int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}

int in[kN], out[kN], sz[kN], dfs_clock;
int val[kN];
int anc[kN];
void dfs(int u, int fa = 0) {
	anc[u] = fa;
	in[u] = ++dfs_clock;
	sz[u] = 1;
	for(auto v : g[u]) if(v.F != fa) {
		val[v.F] = v.S;
		dfs(v.F, u), sz[u] += sz[v.F];
	}
	out[u] = dfs_clock;
}
bool ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
void sub(int &a, int b) {
	a -= b;
	if(a < 0) a += kMod;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1, x, y, d; i < n; i++) {
		scanf("%d%d%d", &x, &y, &d);
		g[x].emplace_back(y, d), g[y].emplace_back(x, d);
	}
	dfs(1); out[0] = dfs_clock;
	int ans = 0;
	for(int i = 1; i <= n; i++) add(ans, 1LL * sz[i] * (n - sz[i]) % kMod * val[i] % kMod);
	printf("%d\n", ans);
	for(int i = 1; i <= n; i++) p[i] = i;
	while(q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		int u = find(x), v = find(y);
		int tmp = 0;
		while(!ancestor(u, y)) {
			add(tmp, 1LL * sz[u] * (n - sz[u]) % kMod * (val[u] - (int)sqrt(val[u] + 0.5)) % kMod);
			val[u] = (int)sqrt(val[u] + 0.5);
			if(val[u] == 1) p[u] = anc[u];
			u = find(anc[u]);
		} 
		while(!ancestor(v, x)) {
			add(tmp, 1LL * sz[v] * (n - sz[v]) % kMod * (val[v] - (int)sqrt(val[v] + 0.5)) % kMod);
			val[v] = (int)sqrt(val[v] + 0.5);
			if(val[v] == 1) p[v] = anc[v];
			v = find(anc[v]);
		} 
		sub(ans, tmp);
		printf("%d\n", ans);
	}
	return 0;
}
