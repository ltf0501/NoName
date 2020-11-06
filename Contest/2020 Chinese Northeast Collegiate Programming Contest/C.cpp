#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, m;
ll pw[12];
ll f(int x) {
	if(!x) return 0;

	ll res = 1, len = ceil(log10(x));
	for(int i = 1; i <= len; i++) 
		res = res * (x % pw[i]) % (x + 1);
	return res;
}
int main() {
	int T; scanf("%d", &T);
	pw[0] = 1;
	for(int i = 1; i <= 10; i++) pw[i] = pw[i - 1] * 10;
	while(T--) {
		scanf("%d%d", &n, &m);
		ll ans = 0;
		for(int nx = f(n); nx != n && m; m--, nx = f(n = nx)) { 
			//printf("nx = %d, n = %d\n", nx, n);
			ans += nx;
		}
		ans += 1LL * m * n;
		printf("%lld\n", ans);
	}
	return 0;
} 
