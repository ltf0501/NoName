#include <bits/stdc++.h>
using namespace std;

constexpr int kInf = 1e9, kC = 1e4;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> as(n);
	vector<array<int, 2>> dist(kC * 5 + 10, {kInf, kInf});
	auto Dist = [&](int x, int p) -> int& { return dist[x + 2 * kC][p]; };
	queue<pair<int, int>> que;
	for (int i = 0; i < n; i++) {
		cin >> as[i];
		que.emplace(as[i], 1);
		Dist(as[i], 1) = 1;
	}
	while (!que.empty()) {
		auto cur_p = que.front();
		auto cur = cur_p.first;
		auto parity = cur_p.second;
		que.pop();
		for (int i = 0; i < n; i++) {
			int nxt = cur + (parity ? -1 : 1) * as[i];
			if (-2 * kC <= nxt && nxt <= 3 * kC && Dist(nxt, !parity) == kInf) {
				Dist(nxt, !parity) = Dist(cur, parity) + 1;
				que.emplace(nxt, !parity);
			}
		}
	}
	int q; cin >> q;
	while (q--) {
		int s, t; cin >> s >> t;
		int mid = (s + t) / 2;
		if (s == t) {
			cout << "0\n";
		} else if ((abs(s - t) & 1)) {
			cout << "-1\n";
		} else {
			int ans = Dist(mid, 1);
			for (int i = 0; i < n; i++) {
				int nxt = 2 * as[i] - s;
				int m = (nxt + t) / 2;
				ans = min(ans, Dist(m, 1) + 1);
			}
			if (ans >= kInf) {
				cout << "-1\n";
			} else {
				cout << ans << '\n';
			}
		}
	}
} 
