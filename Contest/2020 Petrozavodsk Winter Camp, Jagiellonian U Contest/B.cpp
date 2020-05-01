#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = (1 << 20) + 5;
int cnt[kN];
int dp[kN];
int a[kN];
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		for(int i = 1; i < kN; i++) cnt[i] = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++;

		for(int i = 1; i < kN; i++) dp[i] = cnt[i];
		for(int i = 0; i < 20; i++) for(int mask = 0; mask < (1 << 20); mask++) {
			if(mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
		}

		ll ans = 0;
		for(int i = 1; i <= n; i++) ans += dp[a[i]];
		printf("%lld\n", ans);
	}
	return 0;
}
