#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
constexpr int kN = int(5E2 + 10), kInf = int(1E9 + 10), kP = 31, kMod = 998244353;

int dp[kN][kN];
ll hs[kN], p[kN];

ll Hs(int l, int r) {
	ll ans = (hs[r] - hs[l - 1] * p[r - l + 1]) % kMod;
	if (ans < 0) ans += kMod;
	return ans;
}

int count(int x) {
	int ans = 0;
	while (x) {
		x /= 10;
		ans++;
	}
	return ans;
}

int f(int l, int r) {
	if (dp[l][r] > 0) return dp[l][r];
	int len = (r - l + 1), tval;
	ll tmp;
	bool ok;
	dp[l][r] = len;
	for (int i = l + 1; i <= r; i++) dp[l][r] = min(dp[l][r], f(l, i - 1) + f(i, r));
	for (int i = 1; i < len; i++) if (len % i == 0) {
		ok = true;
		tmp = Hs(l, l + i - 1);
		for (int j = i << 1; j <= len; j += i) if (tmp != Hs(l + j - i, l + j - 1)) {
			ok = false;
			break;
		}
		if (ok) {
			tval = f(l, l + i - 1);
			if (tval == 1) dp[l][r] = min(dp[l][r], count(len / i) + tval);
			else dp[l][r] = min(dp[l][r], count(len / i) + 2 + tval);
		}
	}
	return dp[l][r];
}

int solve(string s) {
	int n = int(s.size());
	for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) dp[i][j] = -1;
	for (int i = 1; i <= n; i++) hs[i] = (hs[i - 1] * kP + s[i - 1] - 'a') % kMod;
	for (int i = 1; i <= n; i++) dp[i][i] = 1;
	return f(1, n);
}

void pre() {
	p[0] = 1;
	for (int i = 1; i < kN; i++) p[i] = p[i - 1] * kP % kMod;
	return ;
}

int main() {
	string s;
	int id = 1;
	pre();
	while (true) {
		cin >> s;
		if (s[0] == '0') break;
		else cout << "Case " << id++ << ": " << solve(s) << '\n';
	}
} 
