#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10; 
#define F first
#define S second
vector<int> g[2][maxn];
int num[2][maxn];
int anc[2][20][maxn];
int in[2][maxn], out[2][maxn], dfs_clock;
int cnt2, cnt3;
void dfs(int id, int u, int fa) {
	in[id][u] = ++dfs_clock;
	anc[id][0][u] = fa;
	for(int v : g[id][u]) if(v != fa) {
		dfs(id, v, u);
	}
	out[id][u] = dfs_clock;
}
bool ancestor(int id, int x, int y) {return in[id][x] <= in[id][y] && out[id][x] >= out[id][y];}
int LCA(int id, int x, int y) {
	if(ancestor(id, x, y)) return x;
	if(ancestor(id, y, x)) return y;
	for(int i = 17; i >= 0; i--) if(!ancestor(id, anc[id][i][x], y)) 
		x = anc[id][i][x];
	return anc[id][0][x];
}
void dfs2(int id, int u, int fa) {
	for(int v : g[id][u]) if(v != fa) {
		dfs2(id, v, u);
		num[id][u] += num[id][v];
	}
}
int main() {
	int n; scanf("%d", &n);
	for(int j = 0; j < 2; j++) {
		for(int i = 1; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			g[j][x].push_back(y), g[j][y].push_back(x);
		}
	}
	dfs(0, 1, 0), out[0][0] = dfs_clock;
	dfs_clock = 0;
	dfs(1, 1, 0), out[1][0] = dfs_clock;
	for(int j = 1; j <= 17; j++)
		for(int i = 1; i <= n; i++) anc[0][j][i] = anc[0][j - 1][anc[0][j - 1][i]];
	for(int j = 1; j <= 17; j++)
		for(int i = 1; i <= n; i++) anc[1][j][i] = anc[1][j - 1][anc[1][j - 1][i]];
	for(int i = 1; i <= n; i++) {
		for(int j : g[0][i]) if(i < j)
			num[1][LCA(1, i, j)] -= 2, num[1][i]++, num[1][j]++;
		for(int j : g[1][i]) if(i < j)
			num[0][LCA(0, i, j)] -= 2, num[0][i]++, num[0][j]++;
	}
	dfs2(0, 1, 0);
	for(int i = 2; i <= n; i++) {
		if(num[0][i] == 1) cnt2++;
		if(num[0][i] == 2) cnt3++;
	}
	dfs2(1, 1, 0);
	for(int i = 2; i <= n; i++) {
		if(num[1][i] == 1) cnt2++;
		if(num[1][i] == 2) cnt3++;
	}
	if(cnt2) printf("%d %d\n", 2, cnt2 / 2);
	else printf("%d %d\n", 3, cnt3);
	return 0;
}
