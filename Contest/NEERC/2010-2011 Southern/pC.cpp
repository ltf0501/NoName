#include <bits/stdc++.h>
using namespace std;
const int maxn = 25;
#define lowbit(i) i&-i
int n, m;
char s[maxn][maxn];
int row[maxn], col[maxn];
int dp[1 << maxn];
int lg[1 << maxn];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for(int i = 2; i < (1 << maxn); i++) lg[i] = lg[i >> 1] + 1;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%s", s[i]);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) 
			if(s[i][j] == '*') row[i] |= (1 << j);
	}
	for(int j = 0; j < m; j++) {
		for(int i = 0; i < n; i++)
			if(s[i][j] == '*') col[j] |= (1 << i);
	}
	for(int mask = 1; mask < (1 << m); mask++) {
		dp[mask] = dp[mask - (lowbit(mask))] | col[lg[lowbit(mask)]];
		/*
		printf("mask = %d: dp = %d\n", mask, dp[mask]);
		printf("lowbit = %d, lg = %d, col = %d, dp[mask - lowbit(mask)] = %d\n", lowbit(mask), lg[lowbit(mask)], col[lg[lowbit(mask)]], dp[mask - lowbit(mask)]);
	*/
		}
	int ans = 100;
	for(int mask = 0; mask < (1 << m); mask++) 
		ans = min(ans, max(m - __builtin_popcount(mask), __builtin_popcount(dp[mask]))); 
	printf("%d\n", ans);
	return 0;
}
