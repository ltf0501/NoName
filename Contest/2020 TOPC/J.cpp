#include <stdio.h>
#include <algorithm>
using namespace std;

double Win(int idx, double pF, double pS) {
	idx &= 3;
	if (idx <= 1) return pF;
	else return 1 - pS;
}

double Game(int idx, double pF, double pS) {
	if (idx & 1) {
		double npF, npS;
		npF = 1 - pS, npS = 1 - pF;
		pF = npF, pS = npS;
	}
	double ans = 0, dp[20][20];
	for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) dp[i][j] = 0;
	dp[0][0] = 1;
	for (int i = 0; i < 11; i++) for (int j = 0; j < 11; j++) {
		dp[i + 1][j] += dp[i][j] * Win(i + j, pF, pS);
		dp[i][j + 1] += dp[i][j] * (1 - Win(i + j, pF, pS));
	}
	
	for (int i = 0; i <= 9; i++) ans += dp[11][i];
	//printf("Game, idx = %d, pF = %.3lf, pS = %.3lf\n", idx, pF, pS);
	//for (int i = 0; i < 11; i++, printf("\n")) for (int j = 0; j < 11; j++) printf("%.3lf ", dp[i][j]);

	ans += dp[10][10] * pF * (1. - pS) / (1. - (pF * pS + (1. - pF) * (1. - pS)));
	//if (pS > 0 && pF > 0) ans += dp[10][10] * (pF * pS) / (pF * pS + (1 - pF) * (1 - pS));
	//else {
	//	ans = ans / (1 - dp[10][10]);
	//}
	return ans;
}

double Match(double pF, double pS) {
	double dp[5][5], ans = 0;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) dp[i][j] = 0;
	dp[0][0] = 1;
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
		dp[i + 1][j] += dp[i][j] * Game(i + j, pF, pS);
		dp[i][j + 1] += dp[i][j] * (1 - Game(i + j, pF, pS));
	}
	//printf("Match, pF = %.3lf, pS = %.3lf\n", pF, pS);
	//for (int i = 0; i < 5; i++, printf("\n")) for (int j = 0; j < 5; j++) printf("%.3lf ", dp[i][j]);
	for (int i = 0; i <= 3; i++) ans += dp[4][i];
	return ans;
}



void solve() {
	double a, b;
	scanf("%lf%lf", &a, &b);
	printf("%.20lf\n", Match(a, b));
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}
