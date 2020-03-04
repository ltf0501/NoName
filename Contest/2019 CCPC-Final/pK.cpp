#include <bits/stdc++.h>
using namespace std;
 
constexpr int kN = 200010;
 
int ans[kN];
set<pair<int, int>> st[kN];
vector<int> g[kN];
 
void Insert(pair<int, int> p, set<pair<int, int>> &stx) {
	stx.insert(p);
	auto it = stx.find(p);//stx.insert(p);
	bool redo = false;
	if (it != stx.begin() && prev(it)->second + 1 == p.first) {
		p.first = prev(it)->first;
		stx.erase(prev(it));
		redo = true;
	}
	if (next(it) != stx.end() && p.second + 1 == next(it)->first) {
		p.second = next(it)->second;
		stx.erase(next(it));
		redo = true;
	}
	if (redo) {
		stx.erase(it);
		stx.insert(p);
	}
}
 
void Dfs(int x, int p) {
	pair<int, int> mx = {0, 0};
	for (int y : g[x]) {
		if (y == p) continue;
		Dfs(y, x);
		mx = max(mx, {st[y].size(), y});
	}
	st[x].swap(st[mx.second]);
	for (int y : g[x]) {
		if (y == p || y == mx.second) continue;
		for (auto pr : st[y]) Insert(pr, st[x]);
	}
	Insert({x, x}, st[x]);
	ans[x] = int(st[x].size());
}
 
int main() {
	cin.tie(0); ios_base::sync_with_stdio(0);
	int t; cin >> t;
	int cases = 0;
	while (t--) {
		int n; cin >> n;
		for (int i = 1; i <= n; i++) {
			g[i].clear();
			st[i].clear();
			ans[i] = 0;
		}
		for (int i = 1; i < n; i++) {
			int u, v; cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		Dfs(1, 1);
		cout << "Case #" << ++cases << ":";
		for (int i = 1; i <= n; i++) cout << ' ' << ans[i];
		cout << '\n';
	}
}
