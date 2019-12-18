#include <bits/stdc++.h>
using namespace std;
 
constexpr int kMod = 1E9 + 7;
 
int m, dp[5001][60][60][2], poww10[5001];
int16_t vis[5001][60][60][2], timer;
 
int Dfs(int pos, int sum_diff, int sum_dig, bool at_mx, const string &s) {
	if (pos == int(s.size())) {
		return sum_diff == 0;
	}
	int &ans = dp[pos][sum_diff][sum_dig][at_mx];
	if (vis[pos][sum_diff][sum_dig][at_mx] == timer) return ans;
	vis[pos][sum_diff][sum_dig][at_mx] = timer;
	ans = 0;
	int mx = at_mx ? (s[pos] - '0') : 9;
	for (int i = 0; i <= mx; i++) {
		int d = sum_dig * i - i * poww10[int(s.size()) - pos - 1];
		int tt = ans;
		ans += Dfs(pos + 1, ((sum_diff + d) % m + m) % m, (sum_dig + i) % m, at_mx && i == mx, s);
		ans %= kMod;
	}
	return ans;
}
 
void Sub1(string &s) {
	reverse(s.begin(), s.end());
	for (char &c : s) {
		if (c >= '1') {
			--c;
			break;
		}
		c = '9';
	}
	while (s.size() > 1 && s.back() == '0') s.pop_back();
	reverse(s.begin(), s.end());
}
 
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		string l, r; cin >> l >> r;
		cin >> m;
		poww10[0] = 1;
		for (int i = 1; i <= 5000; i++) {
			poww10[i] = poww10[i - 1] * 10 % m;
		}
		Sub1(l);
		cerr << l << '\n';
		++timer;
		int ans_r = Dfs(0, 0, 0, true, r);
		++timer;
		int ans_l = Dfs(0, 0, 0, true, l);
		cout << (ans_r - ans_l + kMod) % kMod << '\n';
		cerr << ans_l << ' ' << ans_r << '\n';
	}
}
