#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
int n, h;
vector<int> g[kN];

vector<int> leaves;
int deg[kN];

void Dfs(int u, int fa = -1) {
	if(deg[u] == 1) leaves.push_back(u);

	for(int v : g[u]) if(v != fa)
		Dfs(v, u);
}
int main() {
	scanf("%d%d", &n, &h);
	for(int i = 0; i < n - 1; i++) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
		deg[x]++, deg[y]++;
	}
	Dfs(h);

	int sz = int(leaves.size());
	printf("%d\n", (sz + 1) / 2);
	for(int i = 0; i < sz / 2; i++) printf("%d %d\n", leaves[i], leaves[i + sz / 2]);
	if(sz & 1) printf("%d %d\n", leaves[0], leaves.back());
	return 0;
} 
