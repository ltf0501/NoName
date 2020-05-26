#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define PB push_back

constexpr int kN = int(2E6 + 10), INF = int(1E9 + 10); 

vector<int> g[kN];
int match[kN], dist[kN], n, m, a, b;

bool bfs() {
	queue<int> q;
	for (int i = 1; i <= m; ++i) {
		if (!match[i]) dist[i] = 0, q.push(i);
		else dist[i] = INF;
	}
	dist[0] = INF;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == 0) continue;
		for (int v : g[u]) {
			if (dist[match[v]] == INF) {
				dist[match[v]] = dist[u] + 1;
				q.push(match[v]);
			}
		}
	}
	return dist[0] != INF;
}

bool dfs (int u) {
	if (!u) return true;
	for (int v : g[u]) {
		if (dist[match[v]] == dist[u] + 1 && dfs(match[v])) {
			match[u] = v, match[v] = u;
			return true;
		}
	}
	dist[u] = INF;
	return false;
}

int hopcroftKarp() {
	int ret = 0;
	while (bfs()) 
		for (int i = 1; i <= m; ++i) if (!match[i] and dfs(i)) ++ret;
	return ret;
}

int main() {
	while (scanf("%d%d%d%d", &n, &m, &a, &b) != EOF) {
		for (int i = 1; i <= n + n + m; i++) g[i].clear(); 
		memset(match, 0, sizeof(int) * (n + n + m + 1));

		for (int i = 1, l, r; i <= m; i++) {
			scanf("%d%d", &l, &r);
			if (l != b) g[i].PB(m + l + n);
			if (r != a) g[i].PB(m + r); 
		}

		if (hopcroftKarp() == n + n - 2) {
			printf("YES\n");
			for (int i = 1; i <= n; i++) if (match[m + i]) printf("%d ", match[m + i]);
			printf("\n");
			for (int i = 1; i <= n; i++) if (match[m + n + i]) printf("%d ", match[m + n + i]);
			printf("\n");
		}
		else printf("NO\n");
	}
} 
