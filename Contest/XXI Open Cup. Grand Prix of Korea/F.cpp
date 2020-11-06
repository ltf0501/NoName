#pragma GCC optmize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 5e5 + 10;
const ll kInf = ll(2e18);
const ll Large = 1'000'000'000'000;

using Pii = pair<ll, int>;
struct Edge {
  int from, to, cap, flow;
	ll cost;
  Edge() {}
  Edge(int u, int v, int c, int f, ll co)
      : from(u), to(v), cap(c), flow(f), cost(co) {
  }
};
vector<Edge> edges;
vector<int> graph[kN];
struct MCMF {
  int n, m, s, t;
  ll dis[kN];
  //ll h[kN];
  int p[kN];
  void Init(int nn) {
    this->n = nn;
    for (int i = 0; i < n; i++) graph[i].clear();
    edges.clear();
  }
  void AddEdge(
    int from, int to, int cap, ll cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = int(edges.size());
    graph[from].push_back(m - 2);
    graph[to].push_back(m - 1);
  }
  bool Dijkstra(int &max_flow, ll &cost) {
    priority_queue<Pii, vector<Pii>, greater<Pii>>
      pq;
    for (int i = 0; i < n; i++) dis[i] = kInf;
    dis[s] = 0, pq.push(Pii(0, s));
    while (!pq.empty()) {
      Pii u = pq.top();
      pq.pop();
      int v = u.second;
      if (dis[v] < u.first) continue;
			//printf("v = %d, dis = %lld\n", v, dis[v]);
      for (int i = 0; i < int(graph[v].size());
           i++) {
        Edge &e = edges[graph[v][i]];
        if (e.cap > e.flow &&
          dis[e.to] >
            dis[v] + e.cost) {
          dis[e.to] =
            dis[v] + e.cost;
          p[e.to] = graph[v][i];
          pq.push(Pii(dis[e.to], e.to));
        }
      }
    }
    if (dis[t] == kInf) return 0;
    //for (int i = 0; i < n; i++) h[i] += dis[i];
    int d = max_flow;
    for (int u = t; u != s; u = edges[p[u]].from)
      d =
        min(d, edges[p[u]].cap - edges[p[u]].flow);
    max_flow -= d;
    cost += d * dis[t];
    for (int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += d;
      edges[p[u] ^ 1].flow -= d;
    }
    return 1;
  }
  void MincostMaxflow(
    int ss, int tt, int max_flow, ll &cost) {
    this->s = ss, this->t = tt;
    cost = 0;
    //for (int i = 0; i < n; i++) h[i] = 0;
    while (Dijkstra(max_flow, cost) && max_flow) {}
  }
};
MCMF solver;
int main() {
	int n; scanf("%d", &n);
	vector<int> v;
	vector<tuple<int, int, ll>> edges;
	for(int i = 0; i < n; i++) {
		int l, r; ll d; scanf("%d%d%lld", &l, &r, &d);
		r++;
		v.push_back(l), v.push_back(r); 
		edges.emplace_back(l, r, d);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	int nn = int(v.size());

	int s = 0, t = nn;
	solver.Init(t + 1);
	auto GetId = [&](int x) {
		return int(lower_bound(v.begin(), v.end(), x) - v.begin());
	};

	for(auto t : edges) {
		get<0>(t) = GetId(get<0>(t));
		get<1>(t) = GetId(get<1>(t));
		solver.AddEdge(get<0>(t), get<1>(t), 1, -get<2>(t) + Large * (get<1>(t) - get<0>(t)));
	}
	for(int i = 0; i < t; i++) solver.AddEdge(i, i + 1, 2, Large);

	ll cost = 0;
	solver.MincostMaxflow(s, t, 2, cost);
	printf("%lld\n", -(cost - nn * 2 * Large));
	return 0;
} 
