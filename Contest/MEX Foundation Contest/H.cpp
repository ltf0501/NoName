#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>
#include <utility>
#include <stack>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(2E3 + 10), kM = int(4E3 + 10);
bitset<kN> can[kN];
bitset<kM> canedge[kM];
bool ins[kM << 1], went[kM << 1];
vector<int> ng[kN], graph[kN], sccg[kM << 1];
pair<int, int> edge[kN << 1][2];
int d[kN], pos[kN], p[kM << 1], dep[kM << 1], low[kM << 1], t;

bool cmp(pair<int, int> a, pair<int, int> b) {return pos[a.F] < pos[b.F];}

int in[kN], dfs_clock, scc_num;
stack<int> s;
int dfs(int u) {
	s.push(u);
	int lowu = in[u] = ++dfs_clock;
	for(int v : sccg[u]) {
		if(!in[v]) lowu = min(lowu, dfs(v));
		else if(!p[v]) lowu = min(lowu, in[v]);
	}
	if(lowu == in[u]) {
		scc_num++;
		while(true) {
			int x = s.top(); s.pop();
			p[x] = scc_num;
			if(x == u) break;
		}
	}
	return lowu;
}


bool ok(int x) {
	for (int i = 0; i < x; i++) {
		sccg[(i << 1) << 1].clear();
		sccg[(i << 1) << 1 | 1].clear();
		sccg[(i << 1 | 1) << 1].clear();
		sccg[(i << 1 | 1) << 1 | 1].clear();
		went[(i << 1) << 1] = false;
		went[(i << 1) << 1 | 1] = false;
		went[(i << 1 | 1) << 1] = false;
		went[(i << 1 | 1) << 1 | 1] = false;
	}

	for (int i = 0; i < x; i++) {
		sccg[(i << 1) << 1].PB((i << 1 | 1) << 1 | 1);
		sccg[(i << 1 | 1) << 1].PB((i << 1) << 1 | 1);
	}
	
	for (int i = 0; i < x; i++) for (int l = 0; l < 2; l++) {
		for (int j = 0; j <= i; j++) for (int r = 0; r < 2; r++) if ((i << 1 | l) != (j << 1 | r)) {
			if (!canedge[i << 1 | l][j << 1 | r]) {
				sccg[(i << 1 | l) << 1 | 1].PB((j << 1 | r) << 1);
				sccg[(j << 1 | r) << 1 | 1].PB((i << 1 | l) << 1);
			}
		}
	}


	for(int i = 0; i < x * 8; i++) p[i] = in[i] = 0;
	dfs_clock = 0, scc_num = 0;
	t = 0;
	for (int i = 0; i < x; i++) {
		if (!p[(i << 1) << 1]) dfs((i << 1) << 1);
		if (!p[(i << 1) << 1 | 1]) dfs((i << 1) << 1 | 1);
		if (!p[(i << 1 | 1) << 1]) dfs((i << 1 | 1) << 1);
		if (!p[(i << 1 | 1) << 1 | 1]) dfs((i << 1 | 1) << 1 | 1);
	}



	for (int i = 0; i < x; i++) {
		if (p[(i << 1) << 1] == p[(i << 1) << 1 | 1]) return false;
		if (p[(i << 1 | 1) << 1] == p[(i << 1 | 1) << 1 | 1]) return false;
	}

	return true;
}

bool canconnect(int l, int x, int r, int y) {
	if (edge[l][x].S <= edge[r][y].F && can[edge[l][x].S][edge[r][y].F]) return true;
	if (edge[r][y].S <= edge[l][x].F && can[edge[r][y].S][edge[l][x].F]) return true;
	return false;
}

void pre(int n) {
	queue<int> q;
	int nxt, now = n;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) can[i][j] = false;
	for (int i = 1; i <= n; i++) can[i][i] = true;
	for (int i = 1; i <= n; i++) d[i] = int(graph[i].size());
	for (int i = 1; i <= n; i++) if (d[i] == 0) q.push(i);
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		pos[nxt] = now--;
		for (int i : graph[nxt]) can[nxt] |= can[i]; 
		for (int i : ng[nxt]) {
			d[i]--;
			if (d[i] == 0) q.push(i);
		}
	}
	for (int i = 0; i < (n << 1); i++) canedge[i].reset();
	for (int i = 0; i < n; i++) for (int x = 0; x < 2; x++) {
		for (int j = 0; j <= i; j++) for (int y = 0; y < 2; y++) {
			if (canconnect(i, x, j, y)) canedge[i << 1 | x][j << 1 | y] = canedge[j << 1 | y][i << 1 | x] = true;
		}
	}

	
	return ;
}

int main() {
	int n, l, r, mid;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &l, &r);
		edge[i][0] = {l, r};
		ng[r].PB(l);
		graph[l].PB(r);
		scanf("%d%d", &l, &r);
		edge[i][1] = {l, r};
		ng[r].PB(l);
		graph[l].PB(r);
	}
	pre(n);
	l = 0, r = n + 2;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (ok(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n", l);
} 
