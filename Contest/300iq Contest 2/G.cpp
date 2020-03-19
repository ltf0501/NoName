#include <bits/stdc++.h>
using namespace std;
const int kN = 3e5 + 10;
const int kMod = 998244353;

char c[kN];
int nxt[kN];
int f[kN], inv[kN];
int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int a) {return fpow(a, kMod - 2);}
void pre() {
	f[0] = 1;
	for(int i = 1; i < kN; i++) f[i] = 1LL * f[i - 1] * i % kMod;
	inv[kN - 1] = Inv(f[kN - 1]);
	for(int i = kN - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % kMod;
}
int C(int m, int n) {
	if(m < n) return 0;
	int k = 1LL * f[m] * inv[n] % kMod * inv[m - n] % kMod;
	return k;
}
void add(int &a, int b) {
	//printf("add %d\n", b);
	a += b;
	if(a >= kMod) a -= kMod;
}
int main() {
	pre();
	scanf("%s", c);
	int n = strlen(c);
	int ans = 0;
	for(int i = 0; i < n; ) {
		int j = i;
		while(j < n && c[i] == c[j]) j++;
		add(ans, 1LL * C(n - j + i, i) * (j - i) % kMod);
		if(i) {
			for(int k = j - 2; k >= i; k--)
				add(ans, 1LL * C(n - k + i - 2, i - 1) * (k - i + 1) % kMod);
		}
		if(j != n) {
			for(int k = i + 1; k < j; k++)
				add(ans, 1LL * C(n - j + k - 1, k) * (j - k) % kMod);
		}
		for(int k = i; k < j; k++)
			add(ans, 1LL * C(n - j + k, k + 1) % kMod);
		i = j;
	}
	printf("%d\n", ans);
	return 0;
}
