typedef pair<int, int> pii;
#define F first
#define S second
struct Edge {
	int from, to, cap, flow, cost;
	Edge(){}
	Edge(int u, int v, int c, int f, int co): from(u), to(v), cap(c), flow(f), cost(co){}
};

vector<Edge> edges;
vector<int> G[maxn];

struct MCMF {
	int n, m, s, t;
	int dis[maxn];
	int h[maxn];
	int p[maxn];

	void init(int n) {
		this->n = n;
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = (int)edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool dijkstra(int s, int t, int& max_flow, long long& cost) {
		priority_queue<pii, vector<pii>, greater<pii> > pq;
		for(int i = 0; i < n; i++) dis[i] = inf;
		dis[s] = 0, pq.push(pii(0, s));
		while(!pq.empty()) {
			pii u = pq.top(); pq.pop();
			int v = u.S;	
			if(dis[v] < u.F) continue;
			for(int i = 0; i < (int)G[v].size(); i++) {
				Edge& e = edges[G[v][i]];
				if(e.cap > e.flow && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {
					dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
					p[e.to] = G[v][i];
					pq.push(pii(dis[e.to], e.to));
				}
			}
		}
		if(dis[t] == inf) return 0;
		for(int i = 0; i < n; i++) h[i] += dis[i];
		int d = max_flow;
		for(int u = t; u != s; u = edges[p[u]].from) 
			d = min(d, edges[p[u]].cap - edges[p[u]].flow);
		max_flow -= d;
		cost += (long long)d * (long long)h[t];
		for(int u = t; u != s; u = edges[p[u]].from) {
			edges[p[u]].flow += d;
			edges[p[u]^1].flow -= d;
		}
		return 1;
	}

	void MincostMaxflow(int s, int t, int max_flow, long long& cost) {
		this->s = s, this->t = t;
		cost = 0;
		for(int i = 0; i < n; i++) h[i] = 0;
		while(dijkstra(s, t, max_flow, cost) && max_flow);
	}
};
