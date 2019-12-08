#include <bits/stdc++.h>
using namespace std;
 
constexpr int kN = 1010;
 
vector<tuple<int, int, int, int, bool>> dp[kN];
int a[kN];
 
int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i <= n; i++) {
			dp[i].clear();
			dp[i].shrink_to_fit();
		}
		dp[0].emplace_back(0, 0, -1, -1, 0);
		for (int i = 0; i < n; i++) {
			for (auto p : dp[i]) {
				{ // Left
					int l, r, _a, _b;
					bool _c;
					tie(l, r, _a, _b, _c) = p;
					if ((l & (a[i] - 1)) == 0) {
						int nl = l + a[i], nr = r;
						if (nl && nr && __lg(nl) == __lg(nr)) {
							int tmp = __lg(nl);
							nl -= 1 << tmp;
							nr += 1 << tmp;
						}
						dp[i + 1].emplace_back(nl, nr, l, r, 0);
					}
					if (r == 0 && a[i] >= l) dp[i + 1].emplace_back(l + a[i], 0, l, r, 1);
				}
				{ // Right
					int l, r, _a, _b;
					bool _c;
					tie(l, r, _a, _b, _c) = p;
					if ((r & (a[i] - 1)) == 0) {
						int nl = l, nr = r + a[i];
						if (nl && nr && __lg(nl) == __lg(nr)) {
							int tmp = __lg(nl);
							nl -= 1 << tmp;
							nr += 1 << tmp;
						}
						dp[i + 1].emplace_back(nl, nr, l, r, 1);
					}
					if (l == 0 && a[i] >= r) dp[i + 1].emplace_back(0, r + a[i], l, r, 0);
				}
			}
			sort(dp[i + 1].begin(), dp[i + 1].end());
			dp[i + 1] .resize(unique(dp[i + 1].begin(), dp[i + 1].end(), [](auto l, auto r) {
					return get<0>(l) == get<0>(r) && get<1>(l) == get<1>(r);
					}) - dp[i + 1].begin());
		}
		for (auto p : dp[n]) {
			if (__builtin_popcount(get<0>(p)) + __builtin_popcount(get<1>(p)) == 1) {
				int nn = n;
				int l, r, pl, pr;
				bool lr;
				tie(l, r, pl, pr, lr) = p;
				string ans;
				while (nn--) {
					ans.push_back(lr ? 'r' : 'l');
					auto it = lower_bound(dp[nn].begin(), dp[nn].end(), make_tuple(pl, pr, -100, -100, 0));
					tie(l, r, pl, pr, lr) = *it;
				}
				reverse(ans.begin(), ans.end());
				cout << ans << '\n';
				goto End;
			}
		}
		cout << "no\n";
End:;
	}
}
