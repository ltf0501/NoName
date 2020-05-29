#include <bits/stdc++.h>
using namespace std;
const int kN = 1e2 + 10;
const int kInf = 1e7 + 10;
int k;
char A[kN], B[kN];

int dp[kN][kN][kN], pre[kN][kN][kN];
int mn_first[kN][kN][kN], mn_second[kN][kN][kN];
int main() {
	scanf("%d", &k);
	scanf("%s%s", A + 1, B + 1);
	int n = strlen(A + 1), m = strlen(B + 1);

	for(int j = 0; j <= m; j++)for(int a = 0; a <= n; a++)for(int b = 0; b <= m; b++) pre[j][a][b] = kInf;

	for(int j = 0; j <= m; j++) pre[j][0][j] = j;
	for(int i = 0; i <= n; i++)for(int j = 0; j <= m; j++)for(int x = 0; x <= max(n, m); x++)
		mn_first[i][j][x] = mn_second[i][j][x] = kInf; 
	for(int j = k; j <= m; j++) mn_second[0][j][0] = j;
	
	for(int i = 1; i <= n; i++) { 
		for(int j = 0; j <= m; j++)for(int a = 0; a <= n; a++)for(int b = 0; b <= m; b++) dp[j][a][b] = kInf;
		dp[0][i][0] = i;
		if(i >= k) mn_first[i][0][0] = i;

		for(int j = 1; j <= m; j++) {
			for(int a = 0; a <= n; a++) for(int b = 0; b <= m; b++) {
				if(!a && !b) continue;
				int &res = dp[j][a][b]; // dp(i, j, a, b)
				if(!a) {
					res = min(res, /*dp[i][j - 1][x >= k][b - 1]*/ min(mn_first[i][j - 1][b - 1], dp[j - 1][0][b - 1]) + 1);
				}
				else if(!b) {
					res = min(res, /*dp[i - 1][j][a - 1][y >= k]*/ min(mn_second[i - 1][j][a - 1], pre[j][a - 1][0]) + 1);
				}
				else if(A[i] == B[j]) {
					res = min(res, pre[j - 1][a - 1][b - 1] + 1);
				}

				if(a >= k) mn_first[i][j][b] = min(mn_first[i][j][b], res);
				if(b >= k) mn_second[i][j][a] = min(mn_second[i][j][a], res);
				//if(res != kInf) printf("dp[%d][%d][%d][%d] = %d\n", i, j, a, b, res);
			}
		} 
		for(int j = 0; j <= m; j++)for(int a = 0; a <= n; a++)for(int b = 0; b <= m; b++) pre[j][a][b] = dp[j][a][b]; 
	}

	int ans = kInf;
	for(int a = 0; a <= n; a++) {
		for(int b = 0; b <= m; b++) {
			if((a == 0 || a >= k) && (b == 0 || b >= k)) ans = min(ans, pre[m][a][b]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
