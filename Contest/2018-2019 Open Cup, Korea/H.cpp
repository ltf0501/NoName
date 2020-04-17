#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	ll a, b, c, d; cin >> a >> b >> c >> d;
	ll ans = 0;
	const int C = 1000;
	for(int i = 1; i < C; i++) {
		for(int j = 1; i + j < C; j++) if(__gcd(i, j) == 1) {
			ll l = max((a + i - 1) / i, (c + j - 1) / j);
			ll r = min(b / i, d / j);
			ans += max(0ll, (r - l + 1));
		}
	}
	cout << ans << '\n';
	return 0;
}
