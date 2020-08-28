#include <bits/stdc++.h>
using namespace std;
const int kN = 3e3 + 10;
const int kInf = 1e9 + 7;
int n, ee;
int a[kN], b[kN];
int dp[kN][kN][2][2];
int main() {
	scanf("%d", &n);
	int cnt = 0;
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &b[i]);
		if(!a[i] && !b[i]) ee++;
		tot += a[i];
	}
	if(!tot) return puts("0"), 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= ee; j++)
			for(int p = 0; p < 2; p++)
				for(int q = 0; q < 2; q++) dp[i][j][p][q] = kInf;

	for(int j = 0; j <= ee; j++) dp[0][j][1][1] = 0; 
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= ee; j++) {
			for(int p = 0; p < 2; p++) {
				for(int q = 0; q < 2; q++) {
					int &now = dp[i][j][p][q];
					now = dp[i - 1][j][p][1] + (a[i] + b[i] - (b[i] != 0));
					if(!a[i] && !b[i]) {
						if(j > 0) {
							now = min(now, dp[i - 1][j - 1][1][q]);
						}
					}
					if(a[i] || b[i]) {
						int used = min(j, a[i]);
						now = min(now, dp[i - 1][j - used][1][q] + 2 * a[i] - used);
					}
				}
			}
		}
	}
	printf("%d\n", dp[n][ee][0][0]);
	return 0;
} 
