#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;
const double kInf = 1e15;
int a[kN], b[kN], c[kN], d[kN];
double cal(int A, int B, int C, int D) {
	//printf("A = %d, B = %d, C = %d, D = %d\n", A, B, C, D);
	return min({double(A + B), double(C + D), double(1LL * A * C + 1LL * A * D + 1LL * B * C) / double(A + C)});
}
double ccal(int i, int j) {
	//printf("i = %d, j = %d\n", i, j);
	return cal(a[j] - a[i], b[j] - b[i], c[j] - c[i], d[j] - d[i]);
}
double dp[kN];
int main() {
#ifdef ONLINE_JUDGE
	freopen("braess.in", "r", stdin);
	freopen("braess.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
		a[i] += a[i - 1], b[i] += b[i - 1], c[i] += c[i - 1], d[i] += d[i - 1];	
	}
	vector<double> ans(5);
	ans[0] = ccal(0, n);
	ans[1] = 0;
	for(int i = 1; i <= n; i++) ans[1] += ccal(i - 1, i);
	for(int i = 1; i <= n; i++) dp[i] = kInf;	
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < i; j++) {
			dp[i] = min(dp[i], dp[j] + ccal(j, i));
		}
	}
	ans[2] = dp[n];
		
	for(int i = 1; i <= n; i++) dp[i] = 0;
 
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < i; j++) {
			dp[i] = max(dp[i], dp[j] + ccal(j, i));
		}
	}
	//for(int i = 1; i <= n; i++) printf("%12f ", dp[i]); puts("");
	ans[3] = dp[n];
	for(int i = 0; i < 4; i++) printf("%.12f\n", ans[i]);
	return 0;
}
