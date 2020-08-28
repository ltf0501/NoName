#include <bits/stdc++.h>
using namespace std;
#define PB push_back

constexpr int kN = int(3E4 + 10), kInf = int(1E9 + 10);

struct Edge {
	int to, rev, cap;
};

vector<Edge> graph[kN];
int dep[kN], iter[kN], went[kN];

void AddEdge(int u, int v, int cap) {
	//printf("u = %d, v = %d\n", u, v);
	graph[u].PB({v, int(graph[v].size()), cap});
	graph[v].PB({u, int(graph[u].size()) - 1, 0});
	return ;
}

void Bfs(int s, int t) {
	queue<int> q;
	int nxt;
	went[s] = t;
	dep[s] = iter[s] = 0;
	q.push(s);
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		for (Edge i : graph[nxt]) if (i.cap > 0 && went[i.to] != t) {
			went[i.to] = t;
			dep[i.to] = dep[nxt] + 1;
			q.push(i.to);
			iter[i.to] = 0;
		}
	}
	return ;
}

int Dfs(int u, int t, int nv) {
	if (u == t) return nv;
	int tmp;
	for (int &i = iter[u]; i < graph[u].size(); i++) {
		Edge& nxt = graph[u][i];
		if (dep[nxt.to] > dep[u] && nxt.cap > 0) {
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

int Dinic(int s, int t) {
	int ans = 0, now = 0, f;
	for (int i = 0; i < kN; i++) went[i] = 0;
	while (true) {
		Bfs(s, ++now);
		if (went[s] != went[t]) break;
		while ((f = Dfs(s, t, kInf)) > 0) ans += f;
	}
	//printf("flow = %d\n", ans);
	return ans;
}

void Init(int N) {
	for(int i = 0; i <= N; i++) graph[i].clear();
	for(int i = 0; i <= N; i++) dep[i] = iter[i] = went[i] = 0;
}
int n, m, a, b;
int id(int x, int y) {return m * x + y;}
char c[105][105];
bool ok(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && c[x][y] == '0';
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d", &n, &m, &a, &b);
		for(int i = 0; i < n; i++) scanf("%s", c[i]);
		int base = n * m;
		int s = 2 * base, t = 2 * base + 1;
		Init(t + 5);		

		for(int i = 0; i < a; i++) {
			int x; scanf("%d", &x); x--;
			AddEdge(s, id(0, x), 1);
		}
		for(int i = 0; i < b; i++) {
			int x; scanf("%d", &x); x--;
			AddEdge(id(n - 1, x), t, 1);
		}


		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) if(c[i][j] == '0') {
				if(ok(i - 1, j)) AddEdge(id(i, j), id(i - 1, j), 1);
				if(ok(i + 1, j)) AddEdge(id(i, j), id(i + 1, j), 1);
				if(ok(i, j - 1)) AddEdge(id(i, j) + base, id(i, j - 1) + base, 1);
				if(ok(i, j + 1)) AddEdge(id(i, j) + base, id(i, j + 1) + base, 1);

				AddEdge(id(i, j), id(i, j) + base, 1);
				AddEdge(id(i, j) + base, id(i, j), 1);
			}
		}

		puts(Dinic(s, t) == a ? "Yes" : "No");
	}

	return 0;
} 
