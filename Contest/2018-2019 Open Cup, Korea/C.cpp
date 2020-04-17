#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;
const int kMod = 1e9 + 7;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int a) {return fpow(a, kMod - 2);}

int n, p, q, a, b;
char c[kN];
int dp_pre[kN][kN], dp_suf[kN][kN];

int main() {
	scanf("%d%d%d", &n, &p, &q);
	scanf("%s", c + 1);
	scanf("%d%d", &a, &b);

	int sum = p + q;
	p = 1LL * p * Inv(sum) % kMod, q = 1LL * q * Inv(sum) % kMod;

	dp_pre[0][b] = 1;
	for(int i = 1; i <= n; i++) {
		if(c[i] == 'H') {
			for(int x = 0; x <= n; x++)
				dp_pre[i][x] = dp_pre[i - 1][x + 1];
		}
		else {
			for(int x = 1; x <= n; x++)
				dp_pre[i][x] = (1LL * p * dp_pre[i - 1][x] % kMod + 1LL * q * dp_pre[i][x - 1] % kMod) % kMod;
		}
	}

	dp_suf[n + 1][a] = 1;
	for(int i = n; i >= 1; i--) {
		if(c[i] == 'R') {
			for(int x = 0; x <= n; x++)
				dp_suf[i][x] = dp_suf[i + 1][x + 1];
		}
		else {
			for(int x = 1; x <= n; x++)
				dp_suf[i][x] = (1LL * q * dp_suf[i + 1][x] % kMod + 1LL * p * dp_suf[i][x - 1] % kMod) % kMod;
		}
	}

	int ans = 0;
	for(int i = 0; i <= n; i++)
		ans = (ans + 1LL * dp_pre[i][0] * dp_suf[i + 1][0] % kMod) % kMod;
	printf("%d\n", ans);
	return 0;
}
