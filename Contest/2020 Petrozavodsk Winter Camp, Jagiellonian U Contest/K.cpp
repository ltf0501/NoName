#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int dp[144][1 << 12][75];
int tot[75];
char c[144][144];
int fac[210], inv[210];

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
	fac[0] = 1;
	for(int i = 1; i <= 200; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	inv[200] = Inv(fac[200]);
	for(int i = 199; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % kMod;
}

void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
void solve() {
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	for(int i = 0; i < n; i++) scanf("%s", c[i]);
	int N = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) N += c[i][j] == '.';
	}
	if(n < m) {
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < m; j++) swap(c[i][j], c[j][i]);
		}
		swap(n, m);
	}
	memset(dp, 0,sizeof(dp));
	dp[0][0][0] = 1;
	if(c[0][0] == '.') dp[0][1][0] = 1;
	for(int row = 0; row < n; row++) {
		for(int col = 0; col < m; col++) {
			if(row == n - 1 && col == m - 1) continue;
			int i = row * m + col; 

			for(int mask = 0; mask < (1 << m); mask++) { 
				for(int j = 0; j <= k; j++) {
					if(!(mask & (1 << ((col + 1) % m)))) {
						add(dp[i + 1][mask][j], dp[i][mask][j]);
						if(col == m - 1) {
							if(c[row + 1][0] == '.') add(dp[i + 1][mask ^ 1][j], dp[i][mask][j]);
						}
						else {
							if(c[row][col + 1] == '.') {
								add(dp[i + 1][mask ^ (1 << (col + 1))][j], dp[i][mask][j]);
								if(mask & (1 << col)) add(dp[i + 1][mask ^ (1 << col)][j + 1], dp[i][mask][j]);
							}
						}
					}
					else {
						bool flag = (col == m - 1) ? (c[row + 1][0] == '.') : (c[row][col + 1] == '.');
						if(flag) add(dp[i + 1][mask ^ (1 << ((col + 1) % m))][j + 1], dp[i][mask][j]);
					}
				}
			}
		}
	} 
	for(int j = 0; j <= k; j++) tot[j] = dp[n * m - 1][0][j];

	int ans = 0; 
	for(int j = 0; j <= k; j++) {
		int a = 1LL * tot[j] * fac[k] % kMod * inv[k - j] % kMod;
		int b = 1LL * fac[N - 2 * j] * inv[N - 2 * k] % kMod * fpow(inv2, k - j) % kMod;
		int tmp = 1LL * a * b % kMod;

		if(j & 1) tmp = (kMod - tmp) % kMod;
		add(ans, tmp);
	}
	ans = 1LL * ans * fpow(2, k) % kMod;
	printf("%d\n", ans);
}

int main() {
	pre();
	int T; scanf("%d", &T);
	while(T--) solve();
}

