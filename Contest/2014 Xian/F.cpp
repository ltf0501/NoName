#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int kN = 1e6 + 10;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}

int C[kN];
int fac[kN], inv[kN];


int add(int a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if(a < 0) a += kMod;
	return a;
}

int n, m, k;
void pre() {
	C[0] = 1;
	for(int i = 1; i <= k; i++) C[i] = 1LL * C[i - 1] * (m - i + 1) % kMod * Inv(i) % kMod;
	//for(int i = 1; i <= 10; i++) printf("%d ", C[i]); puts("");
}
int f(int d) {
	if(!d) return 0;
	return 1LL * d % kMod * fpow(d - 1, n - 1) % kMod;
}

int Bi(int n, int m) {
	if(n < m) return 0;
	return 1LL * fac[n] * inv[n - m] % kMod * inv[m] % kMod;
}

int main() {
	int T; scanf("%d", &T);
	int cas = 0;

	fac[0] = 1;
	for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	inv[kN - 1] = Inv(fac[kN - 1]);
	for(int i = kN - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % kMod;
	while(T--) {
		scanf("%d%d%d", &n, &m, &k);
		pre();
		int ans = 0, flag = 1;
		for(int i = k; i >= 0; i--) {
			if(flag == 1) {
				ans = add(ans, 1LL * Bi(k, i) * f(i) % kMod);
			}
			else {
				ans = sub(ans, 1LL * Bi(k, i) * f(i) % kMod);
			}
			flag = -flag;
		}
		ans = 1LL * ans * C[k] % kMod;
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
} 
