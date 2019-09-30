#include <bits/stdc++.h>
using namespace std;
const int maxn = 20 * 600 + 10;
const int mod = 1e9 + 7;
int fac[maxn], inv[maxn];
int pw(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % mod;
		n >>= 1, a = 1LL * a * a % mod;
	}
	return res;
}
int INV(int a) {return pw(a, mod - 2);}
void pre() {
	fac[0] = 1;
	for(int i = 1; i < maxn; i++) fac[i] = 1LL * fac[i - 1] * i % mod;
	inv[maxn - 1] = INV(fac[maxn - 1]);
	for(int i = maxn - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}
int C(int n, int m) {
	if(n < m || m < 0) return 0;
	return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int H(int n, int m) {
	if(!n) return 1;
	return C(n + m - 1, m);
}
int main() {
	pre();
	int n, k;
	while(~scanf("%d%d", &n, &k) && n + k) {
			int ans = 2;
			for(int i = 1; i < k; i++) {
				int flag = 1;
				for(int j = 0; ; j++) {
					if((n - 1) * i - j * (k + 1) < 0) break;
					ans = (ans + 1LL * flag * C(n - 1, j) * H(n - 1, (n - 1) * i - j * (k + 1))) % mod;
					if(ans < 0) ans += mod;
					flag = -flag;
				}
			}
			ans = 1LL * n * ans % mod;
			printf("%d\n", ans);
	}
	return 0;
}
