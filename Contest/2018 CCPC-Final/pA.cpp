#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> p(n);
		for (int i = 0; i < n; i++) cin >> p[i].first;
		for (int i = 0; i < n; i++) cin >> p[i].second;
		sort(p.begin(), p.end());
		int64_t sum = 0, cnt = 0;
		for (int i = 0; i < n; i++) {
			if (sum + p[i].second <= m) {
				sum += p[i].second;
				++cnt;
			} else {
				break;
			}
		}
		cout << "Case " << cases << ": " << cnt << '\n';
	}
}
