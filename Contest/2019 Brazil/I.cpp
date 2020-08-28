#include <bits/stdc++.h>
using namespace std;

struct Query { int a, b, k, t, id; };

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n, r; cin >> n >> r;
	vector<pair<int, int>> vec;
	vector<int> temp(n), rnk(n), rnk_to_tmp(n);
	for (int i = 0; i < n; i++) {
		cin >> temp[i];
		vec.emplace_back(temp[i], i);
	}
	sort(vec.begin(), vec.end());
	vector<tuple<int, int, int>> edges;
	while (r--) {
		int u, v, d; cin >> u >> v >> d;
		--u;
		--v;
		edges.emplace_back(u, v, d);
	}
	int q; cin >> q;
	vector<Query> qu(q);
	vector<int> ans(q);
	for (int i = 0; i < q; i++) {
		cin >> qu[i].a >> qu[i].b >> qu[i].k >> qu[i].t;
		--qu[i].a;
		--qu[i].b;
		--qu[i].k;
		qu[i].id = i;
	}
	sort(qu.begin(), qu.end(), [](auto l, auto r) { return l.k < r.k; });
	for (int rev = 0; rev < 2; rev++) {
		int acc = 0;
		for (int i = 0; i < n; i++) {
			if (i && vec[i - 1].first == vec[i].first) rnk[vec[i].second] = rnk[vec[i - 1].second];
			else rnk[vec[i].second] = acc++;
			rnk_to_tmp[acc - 1] = vec[i].first;
		}
		vector<vector<int>> g(n, vector<int>(n));
		for (auto &v : g) fill(v.begin(), v.end(), 0x3f3f3f3f);
		for (auto [u, v, d] : edges) {
			g[u][v] = g[v][u] = d;
		}
		int ptr = 0;
		for (auto [temp, k] : vec) {
			while (ptr < q && ((!rev && (rnk_to_tmp[qu[ptr].k] < temp)) || (rev && (rnk_to_tmp[qu[ptr].k] > temp)))) {
				if (qu[ptr].t == rev) {
					//cerr << "id = " << qu[ptr].id << ": " << rnk_to_tmp[qu[ptr].k] << ' ' << temp << '\n';
					ans[qu[ptr].id] = g[qu[ptr].a][qu[ptr].b];
				}
				++ptr;
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
		while (ptr < q) {
			if (qu[ptr].t == rev) {
				//cerr << "id = " << qu[ptr].id << ": " << -1 << '\n';
				ans[qu[ptr].id] = g[qu[ptr].a][qu[ptr].b];
			}
			++ptr;
		}
		reverse(vec.begin(), vec.end());
	}
	for (int i = 0; i < q; i++) cout << (ans[i] >= 0x3f3f3f3f ? -1 : ans[i]) << '\n';
} 
