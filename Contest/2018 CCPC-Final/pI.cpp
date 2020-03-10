#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		int n; cin >> n;
		vector<pair<int, int>> p(n);
		for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
		sort(p.begin(), p.end());
		map<int, int> id2colval, colval;
		for (int i = 0; i < n; i++) ++id2colval[p[i].second];
		for (auto pr : id2colval) ++colval[pr.second];
		vector<pair<int, int>> ans;
		for (int r = 0; r < n; r++) {
			int r_sum = 0, rr;
			for (rr = r; rr < n && p[r].first == p[rr].first; rr++) {
				auto &v = id2colval[p[rr].second];
				if (--colval[v] == 0) colval.erase(v);
				++colval[--v];
				++r_sum;
			}
			ans.emplace_back(*colval.rbegin());
			ans.back().first += r_sum;
			for (rr = r; rr < n && p[r].first == p[rr].first; rr++) {
				auto &v = id2colval[p[rr].second];
				if (--colval[v] == 0) colval.erase(v);
				++colval[++v];
			}
			r = rr - 1;
		}
		sort(ans.begin(), ans.end(), greater<pair<int, int>>());
		int64_t ans_cnt = 0;
		for (auto pr : ans) {
			if (pr.first != ans[0].first) break;
			ans_cnt += pr.second;
		}
		if (ans[0].first == 2) {
			ans_cnt = 1LL * n * (n - 1) / 2;
		}
		cout << "Case " << cases << ": " << ans[0].first << ' ' << ans_cnt << '\n';
	}
}
