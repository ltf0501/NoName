#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie({});
	ios_base::sync_with_stdio({});
	int p1, q1, p2, q2;
	cin >> p1 >> q1 >> p2 >> q2;
	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		int ans = 0;
		vector<pair<int, int>> v;
		auto f = [&v](int x, int p, int q) {
			if (p <= x && x <= q) {
				v.emplace_back(0, 1);
				v.emplace_back(q - x, -1);
				v.emplace_back(0, 1);
				v.emplace_back(x - p, -1);
			} else if (x < p) {
				v.emplace_back(q - x, -1);
				v.emplace_back(p - x, 1);
			} else {
				v.emplace_back(x - p, -1);
				v.emplace_back(x - q, 1);
			}
		};
		f(x, p1, q1);
		f(x, p2, q2);
		sort(v.begin(), v.end());
		int cnt = 0, last = 0;
		for (auto p : v) {
			if (cnt) {
				ans += p.first - last;
			}
			cnt += p.second;
			last = p.first;
		}
		cout << ans << '\n';
	}
}
