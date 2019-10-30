#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
	freopen("little.in", "r", stdin);
	freopen("little.out", "w", stdout); 
#endif
	int64_t n; cin >> n;
	if (!(n & (n - 1))) {
		cout << "-1\n";
		return 0;
	}
	vector<tuple<int64_t, int64_t, int64_t>> ans;
	for (int i = 1; i <= 64; i++) {
		int64_t xx = int64_t(pow((long double)(n) + 0.5, 1. / i) + 0.5);
		for (int64_t j = max(int64_t(2), xx - 5); j <= xx + 5; j++) {
			auto val = n;
			int cnt1 = 0, cnt2 = 0;
			while (val % j == 0) {
				val /= j;
				++cnt1;
			}
			while (val % (j + 1) == 0) {
				val /= (j + 1);
				++cnt2;
			}
			if (val == 1 && (cnt1 + cnt2) == i) {
				ans.emplace_back(j, cnt1, cnt2);
				break;
			}
		}
	}
	cout << ans.size() << endl;
	for (auto t : ans) {
		auto [j, cnt1, cnt2] = t;
		cout << cnt1 + cnt2;
		for (int k = 0; k < cnt1; k++) cout << ' ' << j;
		for (int k = 0; k < cnt2; k++) cout << ' ' << j + 1;
		cout << '\n';
	}
}
