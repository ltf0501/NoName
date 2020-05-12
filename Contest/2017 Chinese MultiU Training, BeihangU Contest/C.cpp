#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 200010;

multiset<pair<int, int>> st[kN];
vector<int> g[kN];
int64_t ans;
int n, c[kN];

int64_t C2(int64_t x) {
	return 1LL * x * (x - 1) / 2;
}

int Dfs(int x, int p) {
	int sz = 1;
	for (int y : g[x]) {
		if (y == p) continue;
		sz += Dfs(y, x);
	}
	pair<int, int> mx = {0, x};
	for (int y : g[x]) {
		if (y == p) continue;
		mx = max(mx, {st[y].size(), y});
	}
	st[x].swap(st[mx.second]);
	st[x].emplace(c[x], sz);
	for (int y : g[x]) {
		if (y == p || y == mx.second) continue;
		st[x].insert(st[y].begin(), st[y].end());
	}
	if (p != -1) {
		auto it = st[x].lower_bound({c[p], 0});
		int blk_sz = sz;
		while (it != st[x].end() && it->first == c[p]) {
			blk_sz -= it->second;
			it = st[x].erase(it);
		}
		ans -= C2(blk_sz);
	}
	return sz;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int cases = 0;
	while (cin >> n) {
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1; i <= n; i++) st[i].clear();
		vector<int> cs;
		for (int i = 1; i <= n; i++) {
			cin >> c[i];
			cs.push_back(c[i]);
		}
		sort(cs.begin(), cs.end());
		auto colors = int(unique(cs.begin(), cs.end()) - cs.begin());
		ans = C2(n) * colors;
		for (int i = 1; i < n; i++) {
			int x, y; cin >> x >> y;
			g[x].push_back(y);
			g[y].push_back(x);
		}
		Dfs(1, -1);
		auto it = st[1].begin();
		for (int i = 0; i < colors; i++) {
			int blk_sz = n;
			while (it != st[1].end() && it->first == cs[i]) {
				blk_sz -= it->second;
				++it;
			}
			ans -= C2(blk_sz);
		}
		cout << "Case #" << ++cases << ": " << ans << '\n';
	}
} 
