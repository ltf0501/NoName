#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
const int kMod = 1e9 + 7;

int n;
vector<int> g[kN];
int add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
vector<int> Dfs(int u, int fa) {
	vector<int> res(1, 0), res2;
	for(int v : g[u]) if(v != fa) {
		vector<int> tmp = Dfs(v, u);
		if(tmp.size() > res.size()) res.swap(tmp);
		vector<int> tmp_suf(tmp.size()), res_suf(res.size());
		for(int i = int(tmp.size()) - 1; i >= 0; i--)
			tmp_suf[i] = tmp[i] + (i == int(tmp.size()) - 1 ? 0 : tmp_suf[i + 1]); 
		for(int i = int(res.size()) - 1; i >= 0; i--)
			res_suf[i] = res[i] + (i == int(res.size()) - 1 ? 0 : res_suf[i + 1]); 

		int l = int(res.size()), r = int(tmp.size());
		int diff = l - r;


		for(int i = 0; i < diff; i++)
			add(res[i], 1LL * res[i] * tmp_suf[0] % kMod);
		if(u != 1) {
			for(int i = 0; i < int(tmp.size()); i++)
				add(res[i + diff], (1LL * res[i + diff] * tmp_suf[i] + 1LL * tmp[i] * (i == r - 1 ? 0 : res_suf[i + diff + 1])) % kMod), 
				add(res[i + diff], tmp[i]);
		}
		else {
			for(int i = 0; i < int(tmp.size()) - 1; i++)
				add(res[i + diff], (1LL * res[i + diff] * tmp_suf[i + 1] + 1LL * tmp[i] * i == r - 1 ? 0 : res_suf[i + diff + 1]) % kMod),
				add(res[i + diff], tmp[i]);

			
		}
	}
	if(u != 1) {
		res.push_back(1);
		return res;
	}
	else {
		res2.push_back(1);
		return res2;
	}
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1, x, y; i < n; i++) {
			scanf("%d%d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		} 

		int m = int(g[1].size());
		vector<vector<int>> dp(m), dp_pre(m);
		for(int i = 0; i < m; i++) {
			dp[i] = Dfs(g[1][i], 1);
			reverse(dp[i].begin(), dp[i].end());
			dp_pre[i][0] = dp[i][0];
			for(int j = 1; j < int(dp[i].size()); j++) add(dp_pre[i][j], dp_pre[i][j - 1]);
		}

	}
	return 0;
}
