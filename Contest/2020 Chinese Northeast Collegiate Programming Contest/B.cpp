#include <bits/stdc++.h>
using namespace std;

using Pii = pair<int, int>;
constexpr int kInf = 0x3f3f3f3f, kN = 1010;

struct Edge {
	int from, to, cap, flow, cost;
	Edge() = default;
	Edge(int u, int v, int c, int f, int co) : from(u), to(v), cap(c), flow(f), cost(co) {}
};

vector<Edge> edges;
vector<int> graph[kN];
struct MCMF {
	int n, m, s, t;
  int64_t dis[kN], h[kN];
	int p[kN];
	void Init(int nn) {
		this->n = nn;
		for (int i = 0; i < n; i++) graph[i].clear();
		edges.clear();
	}
	void AddEdge(int from, int to, int cap, int cost) {
		edges.emplace_back(from, to, cap, 0, cost);
		edges.emplace_back(to, from, 0, 0, -cost);
		m = int(edges.size());
		graph[from].push_back(m - 2);
		graph[to].push_back(m - 1);
	}
	bool Dijkstra(int &max_flow, int64_t &cost) {
		priority_queue<Pii, vector<Pii>, greater<Pii>> pq;
		for (int i = 0; i < n; i++) dis[i] = kInf;
		dis[s] = 0;
		pq.emplace(0, s);
		while (!pq.empty()) {
			Pii u = pq.top();
			pq.pop();
			int v = u.second;
			if (dis[v] < u.first) continue;
			for (int i = 0; i < int(graph[v].size()); i++) {
				Edge &e = edges[graph[v][i]];
				if (e.cap > e.flow && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {
					dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
					p[e.to] = graph[v][i];
					pq.emplace(dis[e.to], e.to);
				}
			}
		}
		if (dis[t] == kInf) return 0;
		for (int i = 0; i < n; i++) h[i] += dis[i];
		int d = max_flow;
		for (int u = t; u != s; u = edges[p[u]].from) {
			d = min(d, edges[p[u]].cap - edges[p[u]].flow);
		}
		max_flow -= d;
		cost += int64_t(d) * h[t];
		for (int u = t; u != s; u = edges[p[u]].from) {
			edges[p[u]].flow += d;
			edges[p[u] ^ 1].flow -= d;
		}
		return 1;
	}
	void MincostMaxflow(int ss, int tt, int max_flow, int64_t &cost) {
		this->s = ss, this->t = tt;
		cost = 0;
		for (int i = 0; i < n; i++) h[i] = 0;
		while (Dijkstra(max_flow, cost) && max_flow) {}
	}
};

int main() {
	int t; cin >> t;
	while (t--) {
		MCMF solver{};
		int n, m, mod; cin >> n >> m >> mod;
		auto f = [mod](int i, int j) {
			return (i + j) * (i ^ j) % mod;
		};
		vector<int> as(n), bs(n), cs(n);
		for (int i = 0; i < n; i++) cin >> as[i];
		for (int i = 0; i < n; i++) cin >> bs[i];
		for (int i = 0; i < n; i++) cin >> cs[i];
		int s = n * 4 + 1, t = s + 1;
		solver.Init(t + 1);
		for (int i = 0; i < n; i++) {
			solver.AddEdge(s, n + i, 1, 0);
			for (int j = 0; j < n; j++) {
				solver.AddEdge(n + i, j, 1, -(f(as[j], bs[i])));
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				solver.AddEdge(n + n + n + i, n + n + j, 1, -(f(as[i], cs[j])));
			}
		}
		for (int i = 0; i < n; i++) {
			solver.AddEdge(i, n + n + n + i, 1, 0);
		}
		for (int j = 0; j < n; j++) {
			solver.AddEdge(n + n + j, t, 1, 0);
		}
		int64_t cost = 0;
		solver.MincostMaxflow(s, t, m, cost);
		cout << -cost << '\n';
	}
} 
