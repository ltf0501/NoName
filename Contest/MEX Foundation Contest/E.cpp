#include <bits/stdc++.h>
using namespace std;
const int kN = 18;
const int kInf = 1e9 + 10;
typedef pair<int, int> pii;
#define F first
#define S second
int dp[1 << kN][105];
pii pre[1 << kN][105];
int g[kN][kN], tot[1 << kN];
int n, m, s;

int a[kN];
int main() {
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 0, x, y; i < m; i++) {
		scanf("%d%d", &x, &y);
		x--, y--;
		g[x][y]++, g[y][x]++;
	}

	for(int mask = 0; mask < (1 << n); mask++) {
		vector<int> v;
		for(int i = 0; i < n; i++)
			if(mask & (1 << i)) v.push_back(i);

		for(int i = 0; i < int(v.size()); i++)
			for(int j = i + 1; j < int(v.size()); j++) tot[mask] += g[v[i]][v[j]];
	}

	for(int mask = 0; mask < (1 << n); mask++) {
		for(int num = 0; num <= s; num++) {
			int cnt = 0;
			for(int i = 0; i < n; i++) if(mask & (1 << i)) {
				cnt++;
				if(dp[mask][num] < dp[mask ^ (1 << i)][num]) {
					dp[mask][num] = dp[mask ^ (1 << i)][num];
					pre[mask][num] = {mask ^ (1 << i), num};
				}
			}
			
			if(num >= cnt && dp[mask][num] < dp[mask][num - cnt] + tot[mask]) {
				dp[mask][num] = dp[mask][num - cnt] + tot[mask];
				pre[mask][num] = {mask, num - cnt};
			}
		}
	}
	//printf("%d\n", dp[(1 << n) - 1][s]);
	
	int mask = (1 << n) - 1, num = s;
	while(mask) {
		//printf("mask = %d, num = %d\n", mask, num);
		auto p = pre[mask][num];
		if(p.F == mask) {
			for(int i = 0; i < n; i++)
				if(mask & (1 << i)) a[i]++, num--;
		}
		else {
			mask = p.F;
		}
	}
	a[0] += num;
	for(int i = 0; i < n; i++) printf("%d ", a[i]); puts("");
	return 0;
} 
