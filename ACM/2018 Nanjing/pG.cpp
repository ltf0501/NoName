#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int pw(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % mod;
		n >>= 1, a = 1LL * a * a % mod;
	}
	return res;
}
int INV(int a) {return pw(a, mod - 2);}
int main() {
	int T;
	scanf("%d", &T);
	int in6 = INV(6);
	while(T--) {
		int n;
		scanf("%d", &n);
		ll a = 1LL * n * (n + 1) / 2 % mod;
		a = 1LL * a * a % mod;
		ll b = (1LL * n * (n + 1) / 2) % mod * (2LL * n % mod + 1) % mod;
		ll c = 1LL * n * (n + 1) % mod;
		a %= mod, b %= mod, c %= mod;
		//printf("%d %d %d\n", a, b, c);
		ll k = 1LL * (a + b + c) % mod;
		ll ans = 1LL * k * in6 % mod;
		printf("%lld\n", ans);
	}
}
