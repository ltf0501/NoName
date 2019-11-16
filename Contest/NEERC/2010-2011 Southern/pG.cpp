#include <bits/stdc++.h>
using namespace std;
 
bool vis[1010];
int vis2[1010];
vector<int> scc[1010];
vector<pair<int, int>> g[1010], gr[1010], edges;
vector<int> tour;
 
void dfs(int x) {
	vis[x] = true;
	for (auto p: g[x]) {
		int y = p.first;
		if (!vis[y]) dfs(y);
	}
	tour.push_back(x);
}
 
void dfs2(int x, int color) {
	vis2[x] = color;
	scc[color].push_back(x);
	for (auto p: gr[x]) {
		int y = p.first;
		if (!vis2[y]) dfs2(y, color);
	}
}
 
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m; cin >> n >> m;
	if (!m) {
		cout << 1 << '\n';
		cout << 0 << '\n';
		return 0;
	}
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].push_back({v, i});
		gr[v].push_back({u, i});
		edges.push_back({u, v});
	}
	vector<pair<int, int>> allAns;
	for (int j = 0; j < m; j++) {
		g[edges[j].second].push_back({edges[j].first, m});
		gr[edges[j].first].push_back({edges[j].second, m});
		for (int i = 0; i < n; i++) {
			vis[i] = vis2[i] = 0;
			scc[i].clear();
		}
		tour.clear();
		for (int i = 0; i < n; i++) {
			if (!vis[i]) dfs(i);
		}
		int color = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (!vis2[tour[i]]) dfs2(tour[i], ++color);
		}
		pair<int, int> ans = {0, j};
		for (int i = 1; i <= color; i++) {
		       	ans = max(ans, {int(scc[i].size()), j});
		}
		allAns.push_back(ans);
		g[edges[j].second].pop_back();
		gr[edges[j].first].pop_back();
	}
	sort(allAns.begin(), allAns.end(), greater<pair<int, int>>());
	cout << allAns[0].first << '\n';
	vector<int> edgeAns;
	for (auto p: allAns) {
		if (p.first != allAns[0].first) break;
		edgeAns.push_back(p.second + 1);
	}
	cout << edgeAns.size() << '\n';
	sort(edgeAns.begin(), edgeAns.end());
	copy(edgeAns.begin(), edgeAns.end(), ostream_iterator<int>(cout, " "));
}
