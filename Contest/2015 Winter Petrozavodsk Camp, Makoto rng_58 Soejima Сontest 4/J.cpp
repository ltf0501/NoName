#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int kN = 1e5 + 10;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		a = 1LL * a * a % kMod, n >>= 1;
	}
	return res;
}

int Inv(int x) {return fpow(x, kMod - 2);}
int fac[kN], inv[kN];
void pre() {
	fac[0] = 1;
	for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	inv[kN - 1] = Inv(fac[kN - 1]);
	for(int i = kN - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % kMod;
}
int main() {
	int n; scanf("%d", &n);
	pre();
	int ans = fac[n - 2];
	int sum = 0;
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		sum += x;
		ans = 1LL * ans * inv[x - 1] % kMod;
	}
	if(sum != 2 * n - 2) puts("0");
	else printf("%d\n", ans);
	return 0;
} 
