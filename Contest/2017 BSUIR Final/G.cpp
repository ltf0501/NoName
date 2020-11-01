#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll kMod = ll(1e18) + 9;

template<typename T>
T lcm(T n, T m) {
	return n * m / __gcd(n, m);
}
int main() {
	ll n, m;
	scanf("%lld%lld", &n, &m);
	n--, m--;
	ll g = __gcd(n, m);
	ll l = ll(lcm(__int128(n), __int128(m)) % kMod);

	// find x + y = 0, 2g, 4g, 6g, ...
	// find x - y = ..., -2g, 0, 2g, ...
	
	ll ans = 1 + l;

	ll tmp = ll(((__int128(n) / g + 1) * (__int128(m) / g + 1) / 2) % kMod); 
	ans = (ans - tmp) % kMod;
	if(ans < 0) ans += kMod;

	ll add = n / g + m / g;
	ans += add;
	ans %= kMod;
	printf("%lld\n", ans);
	return 0;
} 
