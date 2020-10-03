#include <bits/stdc++.h>
using namespace std;

int last;

template <class VB, class VVP>
void Dfs(int x, VB &used, VB &vis, const VVP &g) {
	last = x;
	vis[x] = 1;
	for (auto pr : g[x]) {
		if (!vis[pr.first]) {
			used[pr.second] = 1;
			Dfs(pr.first, used, vis, g);
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> edges(m);
		vector<uint8_t> used(m), vis(n + 1);
		vector<vector<pair<int, int>>> g(n + 1), gr(n + 1);
		for (int i = 0; i < m; i++) {
			cin >> edges[i].first >> edges[i].second;
			g[edges[i].first].emplace_back(edges[i].second, i);
			gr[edges[i].second].emplace_back(edges[i].first, i);
		}
		Dfs(1, used, vis, g);
		fill(vis.begin(), vis.end(), 0);
		Dfs(1, used, vis, gr);
		int k = 0;
		for (int i = 0; i < m; i++) {
			if (!used[i] && k < m - 2 * n) {
				cout << edges[i].first << ' ' << edges[i].second << '\n';
				++k;
			}
		}
	}
} 
