#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef long long int ll;
typedef long double ld;
ll f[17], dp[17][400], pr_pre[17][400], ex_pre[400];
int seq[20];
ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}
void miin(pair<ll, ll> &a, ll x, ll y) {
	if (ld(a.F) / a.S >  ld(x) / y) a = {x, y};
	return ;
}

void pre() {
	int mx_inv = 16 * 16;
	f[0] = 1;
	dp[0][0] = 1;
	for (int i = 1; i <= 16; i++) {
		for (int j = 0; j <= mx_inv; j++) {
			for (int k = 0; k < i; k++) if (j >= k) dp[i][j] += dp[i - 1][j - k];
			if (j == 0) pr_pre[i][j] = dp[i][j];
			else pr_pre[i][j] = pr_pre[i][j - 1] + dp[i][j];
		}
		f[i] = f[i - 1] * i;
	}
}
void solve() {
	int n, a, b, d, ret, mx_inv, inv;
	pair<ll, ll> ans;
	ll tmp, c;
	scanf("%d%d%d%lld%d", &n, &a, &b, &c, &d);
	mx_inv = (n * (n - 1)) >> 1;
	for (int i = 1; i <= mx_inv; i++) ex_pre[i] = ex_pre[i - 1] + min(a * i, a * (mx_inv - i) + b) * dp[n][i];
	c = c * f[n] + ex_pre[mx_inv];
	ans = {1, 0};
	for (int l = 1; l <= mx_inv; l++) {
		for (int r = mx_inv; mx_inv - r <= l && r >= l; r--) miin(ans, c - ex_pre[r] + ex_pre[l - 1], f[n] - pr_pre[n][r] + pr_pre[n][l - 1]);
	}
	tmp = gcd(ans.F, ans.S);
	ans = {ans.F / tmp, ans.S / tmp};
	while (d--) {
		for (int i = 1; i <= n; i++) scanf("%d", &seq[i]);
		inv = 0;
		for (int j = 1; j <= n; j++) for (int k = j + 1; k <= n; k++) if (seq[j] > seq[k]) inv++;
		ret = min(a * inv, a * (mx_inv - inv) + b);
		if (ans.F < ret * ans.S) printf("%lld/%lld\n", (long long int) ans.F, (long long int) ans.S);
		else printf("%d/1\n", ret);
	}
}

int main() {
	pre();
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
