#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
#define PB push_back
#define F first
#define S second

typedef long long int ll;
constexpr int kN = int(2E5 + 10);
constexpr ll kInf = ll(1E16 + 10);

struct Edge {
	int to, rev;
	ll cap;
};

vector<Edge> graph[kN];
int dep[kN], iter[kN], went[kN];

void AddEdge(int u, int v, ll c) {
	graph[u].PB({v, int(graph[v].size()), c});
	graph[v].PB({u, int(graph[u].size()) - 1, 0});
	return ;
}

void Bfs(int s, int t) {
	queue<int> q;
	int nxt;
	dep[s] = iter[s] = 0;
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
}

ll Dfs(int u, int t, ll nv) {
	if (u == t) return nv;
	ll tmp;
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

ll Dinic(int s, int t) {
	int cnt = 0;
	ll ans = 0, f;
	for (int i = 0; i < kN; i++) went[i] = 0;
	while (true) {
		Bfs(s, ++cnt);
		if (went[s] != went[t]) break;
		while ((f = Dfs(s, t, kInf)) > 0) ans += f;
	}
	return ans;
}

ll p[kN], cap[kN], dis[kN][20], np[kN];
int n, m, s, ori[kN];
vector<pair<int, ll>> v[kN];

bool ok(ll x) {
 	int tot = 1 << s, S = (1 << s) + s, T = (1 << s) + s + 1;
	int idx;
	ll need = 0, tmp;
	for (int i = 1; i <= n; i++) need += p[i];
	for (int i = 0; i < tot; i++) np[i] = 0;
	for (int i = 1; i <= n; i++) {
		idx = 0;
		for (int j = 1; j <= s; j++) if (dis[i][j] <= x) idx |= 1 << (j - 1);
		np[idx] += p[i];
	}
	for (int i = 0; i <= T; i++) graph[i].clear();
	for (int i = 0; i < tot; i++) AddEdge(S, i, np[i]);
	for (int i = 0; i < tot; i++) for (int j = 1; j <= s; j++) if (i & (1 << (j - 1))) {
		AddEdge(i, tot + j - 1, kInf);
	}
	for (int i = 1; i <= s; i++) AddEdge(tot + i - 1, T, cap[i]);

	return Dinic(S, T) == need;
}

int main() {
	int l, r;
	ll c, L = 0, R = kInf, mid;
	pair<ll, int> nxt;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1; i <= n; i++) scanf("%lld", &p[i]);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%lld", &l, &r, &c);
		v[l].PB({r, c});
		v[r].PB({l, c});
	}
	for (int i = 1; i <= s; i++) scanf("%d%lld", &ori[i], &cap[i]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= s; j++) dis[i][j] = kInf;
	
	for (int i = 1; i <= s; i++) {
		dis[ori[i]][i] = 0;
		pq.push({0, ori[i]});
		while (!pq.empty()) {
			nxt = pq.top();
			pq.pop();
			if (dis[nxt.S][i] < nxt.F) continue;
			for (pair<int, ll> j : v[nxt.S]) if (dis[j.F][i] > j.S + nxt.F) {
				dis[j.F][i] = j.S + nxt.F;
				pq.push({j.S + nxt.F, j.F});
			}
		}
	}

	if (ok(0)) printf("0\n");
	else {
		while (R - L > 1) {
			mid = (L + R) >> 1;
			if (ok(mid)) R = mid;
			else L = mid;
		}
		printf("%lld\n", R);
	}
} 
