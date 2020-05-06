#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 4010;

pair<int, int> p[kN];
int g[kN];

int64_t Cross(pair<int, int> o, pair<int, int> a, pair<int, int> b) {
	a.first -= o.first;
	a.second -= o.second;
	b.first -= o.first;
	b.second -= o.second;
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

int64_t Dot(pair<int, int> o, pair<int, int> a, pair<int, int> b) {
	a.first -= o.first;
	a.second -= o.second;
	b.first -= o.first;
	b.second -= o.second;
	return 1LL * a.first * b.first + 1LL * a.second * b.second;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
		cin >> g[i];
	}
	vector<pair<pair<int, int>, int>> pp;
	int64_t ans = INT64_MAX;
	for (int i = 1; i < n; i++) {
		pp.clear();
		auto p1 = p[i], p2 = p[0];
		for (int j = 0; j < n; j++) {
			if (j != i) {
				if (Dot(p1, p2, p[j]) > 0) {
					pp.emplace_back(p[j], g[j]);
				} else if (Dot(p1, p2, p[j]) == 0 && Cross(p1, p2, p[j]) < 0) {
					pp.emplace_back(p[j], g[j]);
				} else {
					pp.emplace_back(make_pair(2 * p1.first - p[j].first, 2 * p1.second - p[j].second), -g[j]);
				}
			}
		}
		sort(pp.begin(), pp.end(), [&](auto l, auto r) {
				return Cross(p1, l.first, r.first) > 0;
		});
		int64_t d = 0;
		for (int j = 0; j < int(pp.size()); j++) {
			d += pp[j].second;
		}
		int64_t ans_tmp = INT64_MAX;
		ans_tmp = min(ans_tmp, abs(d));
		for (int j = 0; j < int(pp.size()); j++) {
			d -= pp[j].second;
			ans_tmp = min(ans_tmp, abs(d));
			d -= pp[j].second;
		}
		cerr << i << ": " << ans_tmp << '\n';
		ans = min(ans, ans_tmp);
	}
	cout << ans << '\n';
} 
