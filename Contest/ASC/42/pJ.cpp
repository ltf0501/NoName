#include <bits/stdc++.h>
using namespace std;
 
int vis[100001], perm[100001], cnt[100001];
vector<int> g[100001];
 
int dfs(int x) {
	if (vis[x]) return vis[x];
	vis[x] = perm[x];
	for (int y : g[x]) vis[x] = min(vis[x], dfs(y));
	return vis[x];
}
 
void dfsSize(int x) {
	vis[x] = true;
	for (int y : g[x]) {
		if (!vis[y]) dfsSize(y);
	}
}
 
int main() {
	freopen("journey.in", "r", stdin);
	freopen("journey.out", "w", stdout);
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	mt19937 rng;
	for (int n, m; cin >> n && n && cin >> m; ) {
		for (int i = 1; i <= n; i++) g[i].clear(), cnt[i] = 0;
		while (m--) {
			int u, v; cin >> u >> v;
			g[u].push_back(v);
		}
		iota(perm + 1, perm + 1 + n, 1);
		for (int tries = 0; tries < 50; tries++) {
			shuffle(perm + 1, perm + 1 + n, rng);
			pair<int, int> res = {n + 1, -1};
			for (int i = 1; i <= n; i++) vis[i] = 0;
			for (int i = 1; i <= n; i++) {
				if (!vis[i]) res = min(res, {dfs(i), i});
			}
			for (int i = 1; i <= n; i++) cnt[i] += vis[i];
		}
		vector<pair<int, int>> vec;
		for (int i = 1; i <= n; i++) vec.emplace_back(cnt[i], i);
		sort(vec.begin(), vec.end());
		if (vec.size() > 50) vec.resize(50);
		pair<int, int> ans{};
		for (auto res : vec) {
			for (int i = 1; i <= n; i++) vis[i] = 0;
			dfsSize(res.second);
			int sz = accumulate(vis + 1, vis + 1 + n, 0);
			ans = max(ans, {sz, res.second});
		}
		cout << ans.second << ' ' << ans.first << '\n';
	}
}
