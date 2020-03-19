#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 300010;

int color[kN], cnt[kN], g_a[kN], g_b[kN], g_s[kN];
int64_t w[kN];
vector<int> color_vec[kN];
set<tuple<int, int, int>> g1[kN], g2[kN];
bool in_queue[kN];

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> w[i];
	vector<int> ans;
	priority_queue<int> poss;
	for (int i = 1; i <= m; i++) {
		int a, b, s; cin >> a >> b >> s;
		g_a[i] = a;
		g_b[i] = b;
		g_s[i] = s;
		g1[a].emplace(b, i, s / 2);
		g2[a].emplace(s / 2, b, i);
		g1[b].emplace(a, i, s / 2);
		g2[b].emplace(s / 2, a, i);
		if (w[a] >= s / 2 || w[b] >= s / 2) {
			poss.push(-i);
			in_queue[i] = true;
		}
	}
	for (int i = 1; i <= n; i++) {
		cnt[i] = 1;
		color[i] = i;
		color_vec[i].push_back(i);
	}
	while (poss.size()) {
		//cerr << "========\n";
		//cerr << "poss: " << poss.size() << '\n';
		int i = -poss.top();
		poss.pop();
		in_queue[i] = false;
		int p = g_a[i], other = g_b[i];
		//cerr << "i: " << i << ", p: " << p << ", other: " << other << '\n';
		if (color[p] == color[other]) continue;
		if (w[color[p]] + w[color[other]] >= g_s[i]) {
			//cerr << "MERGE! " << p << ' ' << other << '\n';
			ans.push_back(i);
			if (cnt[color[p]] < cnt[color[other]]) swap(p, other);
			int c_small = color[other];
			for (int y : color_vec[c_small]) {
				color[y] = color[p];
				color_vec[color[p]].push_back(y);
			}
			g1[color[p]].insert(g1[c_small].begin(), g1[c_small].end());
			g2[color[p]].insert(g2[c_small].begin(), g2[c_small].end());
			cnt[color[p]] += cnt[c_small];
			w[color[p]] += w[c_small];
			while (g2[color[p]].begin() != g2[color[p]].end() &&
					get<0>(*g2[color[p]].begin()) <= w[color[p]]) {
				auto t = *g2[color[p]].begin();
				g2[color[p]].erase(g2[color[p]].begin());
				g1[color[p]].erase({get<1>(t), get<2>(t), get<0>(t)});
				g2[color[other]].erase({get<0>(t), p, get<2>(t)});
				g1[color[other]].erase({p, get<2>(t), get<0>(t)});
				if (!in_queue[get<2>(t)]) {
					poss.push(-get<2>(t));
					in_queue[get<2>(t)] = true;
				}
				//cerr << "INSERTPOS! " << g_a[get<2>(t)] << ' ' << g_b[get<2>(t)] << '\n';
			}
		} else {
			//cerr << "REDUCE! " << p << ' ' << other << '\n';
			int need = g_s[i] - int(w[color[p]] + w[color[other]]);
			g1[color[p]].emplace(other, i, w[color[p]] + need / 2);
			g2[color[p]].emplace(w[color[p]] + need / 2, other, i);
			g1[color[other]].emplace(p, i, w[color[other]] + need / 2);
			g2[color[other]].emplace(w[color[other]] + need / 2, p, i);
		}
		//cerr << "========\n";
	}
	cout << ans.size() << '\n';
	for (int x : ans) cout << x << ' ';
}
