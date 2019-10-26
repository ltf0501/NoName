#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
vector<int> g[maxn];
int n, rt;
int in[maxn], out[maxn], dfs_clock;
int anc[20][maxn];
void dfs(int u, int fa) {
	in[u] = ++dfs_clock;
	anc[0][u] = fa;
	for(int v : g[u]) if(v != fa) {
		dfs(v, u);
	}
	out[u] = dfs_clock;
}
bool ancestor(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
int LCA(int x, int y) {
	if(ancestor(x, y)) return x;
	if(ancestor(y, x)) return y;
	for(int i = 19; i >= 0; i--) if(!ancestor(anc[i][x], y))
		x = anc[i][x];
	return anc[0][x];
}
void init(int n) {
	rt = 1;
	dfs_clock = 0;
	for(int i = 1; i <= n; i++) g[i].clear();
	memset(anc, 0, sizeof(anc));
}
int main() {
	freopen("dynamic.in", "r", stdin);
	freopen("dynamic.out", "w", stdout);
	while(~scanf("%d", &n) && n) {
		init(n);
		for(int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}
		dfs(1, 0);
		out[0] = dfs_clock;
		for(int j = 1; j <= 19; j++)
			for(int i = 1; i <= n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];
		int q;
		scanf("%d", &q);
		while(q--) {
			char c[2];
			scanf("%s", c);
			if(c[0] == '!') {
				scanf("%d", &rt);
			}
			else {
				int u, v;
				scanf("%d%d", &u, &v); 
				if(ancestor(u, rt) && ancestor(v, rt)) {
					if(ancestor(u,v))printf("%d\n",v);
					else printf("%d\n", u);
					continue;
				}
				int l = LCA(u, v);
				if(!ancestor(l, rt) || rt == l) {
					printf("%d\n", l);
					continue;
				}
				if(ancestor(u,v)){
					printf("%d\n",LCA(v,rt));
				}
				else if(ancestor(v,u)){
					printf("%d\n",LCA(u,rt));
				}
				else{
					if(ancestor(LCA(u,rt),LCA(v,rt))){
						printf("%d\n",LCA(v,rt));
					}
					else printf("%d\n",LCA(u,rt));
				}
			}
		}
	}
	return 0;
}
