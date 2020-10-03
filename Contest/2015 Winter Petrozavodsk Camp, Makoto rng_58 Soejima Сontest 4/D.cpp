#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;
const int kMod = 1e9 + 7;

int n;
int a[kN], b[kN];
int same[kN][kN];
int dp[kN][kN], C[kN];

int add(int x, int y) {
	x += y;
	if(x >= kMod) x -= kMod;
	return x;
}
int sub(int x, int y) {
	x -= y;
	if(x < 0) x += kMod;
	return x;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]);

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(a[i] != b[j]) same[i][j] = 0;
			else same[i][j] = same[i - 1][j - 1] + 1;
		}
	}

	C[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < i; j++) C[i] = add(C[i], 1LL * C[j] * C[i - 1 - j] % kMod);
	}

	for(int i = 0; i <= n; i++) dp[i][0] = dp[0][i] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = add(dp[i - 1][j], dp[i][j - 1]);
			for(int k = 1; k <= same[i][j]; k++) dp[i][j] = sub(dp[i][j], 1LL * dp[i - k][j - k] * C[k - 1] % kMod);
		}
	}
	printf("%d\n", dp[n][n]);

	return 0;
} 
