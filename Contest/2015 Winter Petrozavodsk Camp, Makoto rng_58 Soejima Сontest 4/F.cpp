#include <bits/stdc++.h>
using namespace std;

constexpr int kInf = 0x3f3f3f3f;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> as(n), cs(n);
	for (int i = 0; i < n; i++) {
		cin >> as[i] >> cs[i];
		--as[i];
	}
	int m = 1, ans = 0, ok_min = kInf;
	while (m < kInf) {
		vector<int> mp(24, kInf);
		bool ok = true;
		for (int i = 0; i < n; i++) {
			if (mp[cs[i]] == kInf) {
				mp[cs[i]] = as[i] / m;
			}
			if (mp[cs[i]] != as[i] / m) {
					ok = false;
					break;
			}
		}
		sort(mp.begin(), mp.end());
		while (mp.back() == kInf) mp.pop_back();
		ok &= unique(mp.begin(), mp.end()) == mp.end();
		//cerr << m << ' ' << ok << '\n';
		if (ok && ok_min == kInf) ok_min = m;
		if (!ok && ok_min != kInf) {
			ans += m - ok_min;
			ok_min = kInf;
		}
		int n_m = kInf;
		for (int i = 0; i < n; i++) {
			if (as[i] >= m) {
				n_m = min(n_m, as[i] / (as[i] / m) + 1);
			}
		}
		m = n_m;
	}
	if (ok_min != kInf) {
		cout << -1 << '\n';
	} else {
		cout << ans << '\n';
	}
} 
