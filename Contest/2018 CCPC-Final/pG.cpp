#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 10;
const int kMod = 1e9 + 7;
int C[kN][6];
void pre() {
	C[0][0] = 1;
	for(int i = 1; i < kN; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= 5; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % kMod;
	}
}
int main() {
	pre();
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		int n, m; scanf("%d%d", &n, &m);

		int ans = 1LL * (C[n][3] + C[n][4]) * (C[m][3] + C[m][4]) % kMod;
		if(n < 3 && m < 3) ans = 0;
		printf("Case %d: %d\n", cases, ans);
	}
	return 0;
}
