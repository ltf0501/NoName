#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 505;
const ll kInf = 1e18;

int l[kN], r[kN]; 
int s, d, t, n;
unordered_map<int, ll> dp;

ll Dfs(int x) {
	if(x >= s) return 0;
	if(dp.find(x) != dp.end()) return dp[x];

	int nxt_pos = x + d;
	int pos = -1;
	for(int i = 0; i <= n; i++) {
		if(l[i] < nxt_pos && nxt_pos < r[i]) nxt_pos = l[i];
		if(l[i] >= x && pos == -1) pos = i;
	}

	int cnt = (r[pos] - x) / d; 
	if(cnt > 1) return 1LL * (cnt - 1) * min(t, d) + Dfs(x + (cnt - 1) * d);

	ll res = kInf;
	for(int i = pos; i <= n; i++) {
		if(r[i] - l[pos] <= d) res = min(res, max(0, r[i] - d - x) + t + Dfs(r[i]));
	}

	res = min(res, t + Dfs(nxt_pos));
	if(pos == n) res = min(res, ll(s - x));
	return dp[x] = res;
}
int main() {
	scanf("%d%d%d", &s, &d, &t);
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d%d", &l[i], &r[i]);
	l[n] = r[n] = s;

	ll ans = Dfs(0);
	printf("%lld\n", ans);
	return 0;
}

