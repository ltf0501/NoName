#include <bits/stdc++.h>
using namespace std;
 
int par[10010];
int64_t dp[10010];
pair<int, int> ti[10010];
 
int main() {
	cin.tie(nullptr); ios_base::sync_with_stdio(false);
	freopen("iq.in", "r", stdin);
	freopen("iq.out", "w", stdout);
	int n;
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) {
			cin >> ti[i].first;
			ti[i].second = i;
		}
		sort(ti, ti + n);
		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			dp[i] = INT64_MAX;
			for (int j = 0; j < i; j++) {
				auto tmp = dp[j] + 1ll*(n - j) * ti[i - 1].first;
				if (tmp < dp[i]) dp[i] = tmp, par[i] = j;
			}
		}
		vector<vector<int>> ans;
		for (int i = n; i; i = par[i]) {
			vector<int> tmp;
			for (int j = par[i]; j < i; j++) tmp.push_back(ti[j].second);
			sort(tmp.begin(), tmp.end());
			ans.push_back(tmp);
		}
		reverse(ans.begin(), ans.end());
		cout << dp[n] << '\n';
		cout << ans.size() << '\n';
		for (auto &v : ans) {
			cout << v.size();
			for (int x : v) cout << ' ' << x + 1;
			cout << '\n';
		}
#ifdef DEBUG
		for(int i=1;i<=n;i++)printf("dp[%d]=%lld\n",i,dp[i]);
#endif
	}
}
