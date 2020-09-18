#include <bits/stdc++.h>
using namespace std;

constexpr int64_t kInf = 1e18;
template <class T>
using Heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	int s, t; cin >> s >> t;
	vector<int64_t> dist(n + n, kInf);
	vector<vector<pair<int, int>>> g(n + n, vector<pair<int, int>>());
	vector<int> g_st(n + n);
	while (m--) {
		int u, v, w; cin >> u >> v >> w;
		g[v + n].emplace_back(u, w);
		g[v].emplace_back(u + n, w);
		++g_st[u + n];
		++g_st[u];
	}
	Heap<pair<int64_t, int>> pq;
	pq.emplace(dist[t] = 0, t);
	pq.emplace(dist[t + n] = 0, t + n);
	vector<uint8_t> vis(n + n);
	while (!pq.empty()) {
		int64_t d;
		int cur;
		tie(d, cur) = pq.top();
		pq.pop();
		if (vis[cur]) continue;
		--g_st[cur];
		if (cur < n) { // A
			if (g_st[cur] > 0) continue;
		}
		dist[cur] = d;
		vis[cur] = 1;
		for (auto _pr : g[cur]) {
			int nxt, w;
			tie(nxt, w) = _pr;
			pq.emplace(dist[cur] + w, nxt);
		}
	}
	if (!vis[s]) {
		cout << "infinity\n";
	} else {
		cout << dist[s] << '\n';
	}
} 
