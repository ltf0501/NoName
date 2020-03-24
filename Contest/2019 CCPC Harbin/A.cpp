#include <bits/stdc++.h>
using namespace std;

struct Limit {
	int l, r, k;
} v1[3010], v2[3010];

bool in_q[3010];
int dist[3010];
vector<pair<int, int>> g[3010];

int main() {
	int t; cin >> t;
	while (t--) {
		int n, m1, m2; cin >> n >> m1 >> m2;
		for (int i = 0; i < m1; i++) {
			cin >> v1[i].l >> v1[i].r >> v1[i].k;
		}
		for (int i = 0; i < m2; i++) {
			cin >> v2[i].l >> v2[i].r >> v2[i].k;
		}
		int l = 0, r = n;
		while (l != r) {
			int m = (l + r) >> 1;
			for (int i = 0; i <= n; i++) g[i].clear();
			g[0].emplace_back(m, n);
			g[n].emplace_back(-m, 0);
			for (int i = 1; i <= n; i++) {
				g[i - 1].emplace_back(1, i);
				g[i].emplace_back(0, i - 1);
			}
			for (int i = 0; i < m1; i++) {
				auto &x = v1[i];
				g[x.r].emplace_back(-x.k, x.l - 1);
			}
			for (int i = 0; i < m2; i++) {
				auto &x = v2[i];
				g[x.l - 1].emplace_back(m - x.k, x.r);
			}
			memset(dist, 0x3f, sizeof(dist));
			memset(in_q, false, sizeof(in_q));
			dist[0] = 0;
			queue<int> q;
			q.push(0);
			bool fail = false;
			while (q.size()) {
				int cur = q.front();
				q.pop();
				in_q[cur] = false;
				for (auto p : g[cur]) {
					if (dist[cur] + p.first < dist[p.second]) {
						dist[p.second] = dist[cur] + p.first;
						if (dist[p.second] < 0) {
							fail = true;
							goto End;
						}
						if (!in_q[p.second]) {
							in_q[p.second] = true;
							q.push(p.second);
						}
					}
				}
			}
End:;
			if (fail) l = m + 1;
			else r = m;
		}
		cout << l << '\n';
	}
} 
