      #include <bits/stdc++.h>
using namespace std;

uint64_t dp[71][10][2][2], n;
string str;
bool isInc[71];

uint64_t dfs(int pos, int last, bool mx, bool inc) {
	if (pos == n) {
		return 1;
	}
	uint64_t &ans = dp[pos][last][mx][inc];
	if (ans) return ans;
	if (mx) {
		ans = dfs(pos + 1, str[pos] - '0', true, isInc[pos]);
		for (int i = 0; i < str[pos] - '0'; i++) {
			ans += dfs(pos + 1, i, false, i >= last && isInc[pos]);
		}
	} else {
		if (inc) {
			for (int i = 0; i < last; i++) ans += dfs(pos + 1, i, false, false);
			for (int i = last; i < 10; i++) ans += dfs(pos + 1, i, false, true);
		} else {
			for (int i = 0; i <= last; i++) ans += dfs(pos + 1, i, false, false);
		}
	}
	// cout << pos << ' ' << last << ' ' << mx << ' ' << inc << ' ' << ans << '\n';
	return ans;
}

int main() {
	int t; cin >> t;
	while (t--) {
		memset(dp, 0, sizeof(dp)), memset(isInc, 0, sizeof(isInc));
		cin >> str;
		n = (int)str.size();
		bool fail = false;
		isInc[0] = true;
		for (int i = 1; i < n; i++) {
			if (!isInc[i - 1] && str[i - 1] < str[i]) fail = true;
			isInc[i] = isInc[i - 1] && (str[i] >= str[i - 1]);
		}
		if (fail) {
			cout << "-1\n";
		} else {
			cout << dfs(0, 0, true, true) - 1 << '\n';
		}
	}
}
