struct Edge {
	int from, to, cap, flow, cost;
	Edge(){}
	Edge(int u, int v, int c, int f, int co): from(u), to(v), cap(c), flow(f), cost(co){}
};
vector<Edge> edges;
vector<int> G[maxn];

struct MCMF {
	int n, m, s, t;
	int inq[maxn];
	int dis[maxn];
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

	bool BellmanFord(int s, int t, int& max_flow, long long& cost) {
		for(int i = 0; i < n; i++) dis[i] = inf;
		memset(inq, 0, sizeof(inq));
		dis[s] = 0, inq[s] = 1, p[s] = 0, a[s] = inf;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = 0;
			for(int i = 0; i < (int)G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if(e.cap > e.flow && dis[e.to] > dis[u] + e.cost) {
					dis[e.to] = dis[u] + e.cost;
					p[e.to] = G[u][i];
					if(!inq[e.to]) {
						q.push(e.to);
						inq[e.to] = 1;
					}
				}
			}
		}
		
		if(dis[t] == inf) return 0;
		int d = max_flow;
		for(int u = t; u != s; u = edges[p[u]].from) 
			d = min(d, edges[p[u]].cap - edges[p[u]].flow);
		max_flow -= d;
		cost += (long long)d * (long long)dis[t];
		for(int u = t; u != s; u = edges[p[u]].from) {
			edge[p[u]].flow += a[t];
			edge[p[u]^1].flow -= a[t];
		}
		return 1;
	}

	void MincostMaxflow(int s, int t, int max_flow, long long& cost) {
		this->s = s, this->t = t;
		cost = 0;
		while(BellmanFord(s, t, flow, max_flow, cost));
	}
};
