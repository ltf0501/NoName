#include <bits/stdc++.h>
using namespace std;

#define PB push_back
constexpr int kInf = int(1E9 + 10);

bool board[12][12];
int w[12][12], now[12], dp[1 << 24];

int ABS(int x) {return x >= 0 ? x : -x;}

int main() {
	string s;
	int n, nx, ny;
	vector<int> wcandi, bcandi; 
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < n; j++) if (s[j] == 'B') board[i][j] = true;
		else board[i][j] = false;
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> w[i][j];
	for (int i = (1 << (n << 1)) - 1; i >= 0; i--) dp[i] = kInf;
	dp[((1 << n) - 1)] = 0;

	for (int i = 0; i < (1 << (n << 1)); i++) if (__builtin_popcount(i) == n) {
		nx = 0, ny = -1;
		// 1 |
		// 0 -
		for (int pos = 1; pos <= (1 << (n << 1)); pos <<= 1) {
			if (i & pos) ny++;
			else now[nx++] = ny;
		}
		//printf("%d :", i);
		//for (int j = 0; j < n; j++) printf(" %d", now[j]);
		//printf("\n");
		wcandi.clear();
		bcandi.clear();
		if (now[0] >= 0) {
			if (board[0][now[0]]) bcandi.PB(0); 
			else wcandi.PB(0);
			dp[i ^ (3 << now[0])] = min(dp[i ^ (3 << now[0])], dp[i] + w[0][now[0]]);
			//printf("%d to %d, cost = %d\n", i, i ^ (3 << (0 + now[0])), w[0][now[0]]);
		}
		for (int j = 1; j < n; j++) if (now[j - 1] < now[j]) {
			if (board[j][now[j]]) bcandi.PB(j);
			else wcandi.PB(j);
			//printf("%d to %d, cost = %d\n", i, i ^ (3 << (j + now[j])), w[j][now[j]]);
			dp[i ^ (3 << (j + now[j]))] = min(dp[i ^ (3 << (j + now[j]))], dp[i] + w[j][now[j]]);
		}
		for (int x : wcandi) for (int y : bcandi) {
			dp[i ^ (3 << (x + now[x])) ^ (3 << (y + now[y]))] = 
				min(dp[i ^ (3 << (x + now[x])) ^ (3 << (y + now[y]))], dp[i] + ABS(w[x][now[x]] - w[y][now[y]]));
			//printf("%d to %d, cost = %d\n", i, i ^ (3 << (x + now[x])) ^ (3 << (y + now[y])), ABS(w[x][now[x]] - w[y][now[y]]));
		}
		//printf("dp[%d] = %d\n", i, dp[i]);
	}
	cout << dp[((1 << n) - 1) << n] << '\n';
} 
