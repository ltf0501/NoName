#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(1E2 + 10);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	int lc, pc, lm, pm, t, d; cin >> lc >> pc >> lm >> pm >> t >> d;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	sort(a.begin(), a.end(), greater<int>());
	multiset<int, greater<int>> s_a, s_b0, s_b1, s_c;
	int64_t excess = 0, sum_b1 = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] >= lm) {
			s_b0.insert(a[i]);
			excess += min(d, a[i] - lm);
		} else {
			s_b1.insert(a[i]);
			sum_b1 += a[i];
		}
	}
	int64_t ans = INT64_MAX, mov_a = 0;
	for (int i = 0; i <= n; i++) {
		//
		//0 0 0 0 1 1 0
		//1 1 -15 1 0 0 1
		//2 -7 -15 2 0 0 1
		//
		auto mov = int64_t(s_b1.size()) * lm - sum_b1;
		if (excess - mov >= 0 && (s_b1.empty() || *s_b1.rbegin() >= lm - d)) {
			int64_t cur = int64_t(s_a.size()) * pc + int64_t(s_b0.size() + s_b1.size()) * pm + (mov + mov_a) * t;
			ans = min(ans, cur);
		}
		if (i == n) break;
		int nxt = [&]() {
			if (s_b0.size()) {
				auto r = *s_b0.begin();
				s_b0.erase(s_b0.begin());
				excess -= min(d, r - lm);
				return r;
			} else if (s_b1.size()) {
				auto r = *s_b1.begin();
				s_b1.erase(s_b1.begin());
				sum_b1 -= r;
				return r;
			} else if (s_c.size()) {
				auto r = *s_c.begin();
				s_c.erase(s_c.begin());
				excess -= min(d, r - 1);
				return r;
			}
			assert(0);
		}();
		s_a.insert(nxt);
		if (nxt < lc - d) break;
		if (nxt >= lc) {
			excess += min(d, nxt - lc);
		} else {
			mov_a += lc - nxt;
			excess -= lc - nxt;
		}
		for (int j = 1; j < k; j++) {
			int nxt_c = [&]() {
				if (s_b1.size()) {
					auto r = *s_b1.rbegin();
					s_b1.erase(s_b1.find(r));
					sum_b1 -= r;
					return r;
				} else if (s_b0.size()) {
					auto r = *s_b0.rbegin();
					s_b0.erase(s_b0.find(r));
					excess -= min(d, r - lm);
					return r;
				}
				return -1;
			}();
			if (nxt_c == -1) break;
			s_c.insert(nxt_c);
			excess += min(d, nxt_c - 1);
		}
	}
	cout << (ans == INT64_MAX ? -1 : ans) << '\n';
} 
