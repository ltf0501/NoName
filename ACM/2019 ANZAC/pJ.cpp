#include <bits/stdc++.h>
using namespace std;

const char *CHR = "ROYGBIV";

int64_t ddiisstt[(7 * 7 * 7 + 1) << 7];
vector<pair<int, int64_t> > g[(7 * 7 * 7 + 1) << 7];

int main() {
	int n; cin >> n;
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v, dist;
		char chrd;
		cin >> u >> v >> dist >> chrd;
		int d = strchr(CHR, chrd) - CHR;
		for (int j = 0; j < (1 << 7); j++) {
			g[u << 7 | j].push_back({ v << 7 | j | (1 << d), dist });
			g[v << 7 | j].push_back({ u << 7 | j | (1 << d), dist });
		}
	}
	memset(ddiisstt, 0x3f, sizeof(ddiisstt));
	priority_queue<pair<int64_t, int>, vector<pair<int64_t, int> >, greater<pair<int64_t, int> > > pq;
	pq.push({ 0, 1 << 7 });
	ddiisstt[1 << 7] = 0;
	while (pq.size()) {
		auto p = pq.top(); pq.pop();
		if (ddiisstt[p.second] < p.first) continue;
		for (auto &nxt: g[p.second]) {
			int64_t nd = ddiisstt[p.second] + nxt.second;
			if (ddiisstt[nxt.first] > nd) {
				ddiisstt[nxt.first] = nd;
				pq.push({ nd, nxt.first });
			}
		}
	}
	cout << ddiisstt[1 << 7 | ((1 << 7) - 1)] << '\n';
}
