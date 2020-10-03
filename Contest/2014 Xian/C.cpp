#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define PB push_back

constexpr int kN = int(1E2 + 10), kInf = int(1E9 + 10);
struct Edge {
	int to, rev;
	double cap;
};

vector<Edge> graph[kN];
int iter[kN], dep[kN], went[kN];
void AddEdge(int u, int v, double c) {
	graph[u].PB({v, int(graph[v].size()), c});
	graph[v].PB({u, int(graph[u].size()) - 1, c});
	return ;
}

void Bfs(int s, int t) {
	queue<int> q;
	int nxt;
	iter[s] = dep[s] = 0;
	went[s] = t;
	q.push(s);
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		for (Edge i : graph[nxt]) if (i.cap > 0 && went[i.to] != t) {
			went[i.to] = t;
			dep[i.to] = dep[nxt] + 1;
			iter[i.to] = 0;
			q.push(i.to);
		}
	}
	return ;
}

double Dfs(int u, int t, double nv) {
	if (u == t) return nv;
	double tmp;
	for (int &i = iter[u]; i < int(graph[u].size()); i++) {
		Edge& nxt = graph[u][i];
		if (nxt.cap > 0 && dep[nxt.to] > dep[u]) {
			tmp = Dfs(nxt.to, t, min(nv, nxt.cap));
			if (tmp > 0) {
				nxt.cap -= tmp;
				graph[nxt.to][nxt.rev].cap += tmp;
				return tmp;
			}
		}
	}
	return 0;
}

double Dinic(int s, int t) {
	double ans = 0, f;
	int cnt = 0;
	for (int i = 0; i < kN; i++) went[i] = 0;
	while (true) {
		Bfs(s, ++cnt);
		if (went[s] != went[t]) break;
		while ((f = Dfs(s, t, kInf)) > 0) ans += f;
	}
	return ans;
}

int deg[kN], a[kN];

void solve() {
	int n, tot, S, T;
	double l, r, mid, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) deg[i] = 0;
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (a[i] > a[j]) {
		deg[i]++;
		deg[j]++;
	}
	tot = n * (n - 1);
	l = 0, r = tot;
	S = 0, T = n + 1;
	for (int i = 0; i < 100; i++) {
		mid = (l + r) / 2;
		for (int j = 0; j <= T; j++) graph[j].clear();
		for (int j = 1; j <= n; j++) for (int k = j + 1; k <= n; k++) {
			if (a[j] > a[k]) {
				AddEdge(j, k, 1); 
			}
		}
		for (int j = 1; j <= n; j++) AddEdge(S, j, tot);
		for (int j = 1; j <= n; j++) AddEdge(j, T, tot + mid * 2 - deg[j]);
		tmp = Dinic(S, T);
		if (tmp < tot * n) l = mid;
		else r = mid;
	}
	printf("%.20lf\n", r);
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: ", i);
		solve();
	}
} 
