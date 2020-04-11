#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int inv2 = 5e8 + 4;
const int kN = 2e5 + 10;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int a) {return fpow(a, kMod - 2);}
int invp2[kN], fac[kN], invf[kN];
void pre() {
	fac[0] = 1;
	for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	invf[kN - 1] = Inv(fac[kN - 1]);
	for(int i = kN - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % kMod;
	invp2[0] = 1;
	for(int i = 1; i < kN; i++) invp2[i] = 1LL * invp2[i - 1] * inv2 % kMod;
}
int f(int n) {
	return 1LL * fac[2 * n] * invp2[n] % kMod * invf[n] % kMod; //(2n)! / (2^n n!)
}
void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
int main() {
	int n; scanf("%d", &n);
	if(n == 1) return puts("1"), 0;
	pre();
	int ans = 0;
	for(int a = 2; a < 2 * n; a++) {
		int tmp = 1LL * (a / 2) * fpow(2 * n - a, (a + 1) / 2 - 1) % kMod * f(n - (a + 1) / 2) % kMod;
		//printf("a = %d: tmp = %d\n", a, tmp);
		add(ans, tmp);
	}
	//printf("tot = %d\n", ans);
	ans = 1LL * ans * Inv(f(n)) % kMod;
	//printf("f(n) = %d\n", f(n));
	printf("%d\n", ans);
	return 0;
}
