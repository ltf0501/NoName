#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;
const int kMod = 1e9 + 9;
int n;
map<int, int> mp;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		a = 1LL * a * a % kMod, n >>= 1;
	}
	return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}
int fac[kN];
int dp[kN];
int a[kN];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);

	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;

	dp[0] = 1; 
	for(int i = 1; i <= n; i++) {
		int tot = 1, cur = 1, cnt = 1;
		int tmp = 0;
		for(int j = i; j >= 1; j--) {
			tmp = (tmp + 1LL * dp[j - 1] * tot % kMod) % kMod;
			if(j == i) tot = 1;
			else {
				if(a[j] != a[j + 1]) {
					cur = 1LL * cur * fac[cnt] % kMod;
					cnt = 1;
					tot = 1LL * fac[i - j + 1] * Inv(cur) % kMod;
				}
				else {
					cnt++;
					tot = 1LL * fac[i - j + 1] * Inv(cur) % kMod * Inv(fac[cnt]) % kMod;
				}
			}
		}
		//printf("tot = %d, tmp = %d\n", tot, tmp);
		dp[i] = (tot - tmp + kMod) % kMod;
	}

	//for(int i = 1; i <= n; i++) printf("%d ", dp[i]); puts("");
	int ans = dp[n];
	printf("%d\n", ans);
	
	return 0;
} 
