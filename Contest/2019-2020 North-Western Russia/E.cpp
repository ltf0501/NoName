#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(2E5 + 10), LOGN = 20;
vector<int> graph[kN];
int a[kN], d[kN], p[LOGN][kN], dep[kN];
bool went[kN], two[kN];

void dfs(int pos, int from) {
	dep[pos] = dep[from] + 1;
	p[0][pos] = from;
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	return ;
}

int LCA(int l, int r) {
	if (dep[l] < dep[r]) swap(l, r);
	for (int i = LOGN - 1; i >= 0; i--) if (dep[p[i][l]] >= dep[r]) l = p[i][l];
	if (l == r) return l;
	for (int i = LOGN - 1; i >= 0; i--) if (p[i][l] != p[i][r]) l = p[i][l], r = p[i][r];
	return p[0][l];
}

int dis(int l, int r) {
	return dep[l] + dep[r] - dep[LCA(l, r)] * 2;
}

int main() {
	int n, m, posi, nxt, l, r, dist;
	queue<int> q;
	scanf("%d%d", &n, &m);
	if (m == 1) {
		printf("YES\n1\n");
		return 0;
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	dfs(1, 1);
	for (int i = 1; i < LOGN; i++) for (int j = 1; j <= n; j++) p[i][j] = p[i - 1][p[i - 1][j]];
	for (int i = 1; i <= n; i++) went[i] = false;
	for (int i = 1; i <= n; i++) two[i] = false;
	for (int i = 1; i <= m; i++) q.push(a[i]);
	for (int i = 1; i <= m; i++) went[a[i]] = true;
	for (int i = 1; i <= m; i++) d[a[i]] = 0;
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		if (two[nxt]) posi = nxt;
		for (int i : graph[nxt]) if (!went[i]) {
			went[i] = true;
			d[i] = d[nxt] + 1;
			q.push(i);
		}
		else if (d[i] == d[nxt] + 1) two[i] = true;
	}
	dist = dis(posi, a[1]);
	for (int i = 2; i <= m; i++) if (dist != dis(posi, a[i])) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n%d\n", posi);
} 
