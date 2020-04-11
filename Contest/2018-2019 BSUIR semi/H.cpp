#include <bits/stdc++.h>
using namespace std;

string n;
bool vis[100][2];
int64_t dp[100][2];

int64_t Dfs(int p, bool full) {
	if (p == int(n.size())) return 1;
	if (vis[p][full]) return dp[p][full];
	vis[p][full] = true;
	auto &ans = dp[p][full];
	ans = 0;
	// 1 2 3 5 8
	for (int k : {0, 4, 6, 7, 9}) {
		if (!full || k <= n[p] - '0') ans += Dfs(p + 1, (k == n[p] - '0') && full);
	}
	return ans;
}

int main() {
	int t; cin >> t;
	while (t--) {
		memset(vis, 0, sizeof(vis));
		cin >> n;
		cout << Dfs(0, true) << '\n';;
	}
}
