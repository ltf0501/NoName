#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 6, kS = 4;

bool vis[kN * kS][kN * kS][1 << (kN + kN)];
int dp[kN * kS][kN * kS][1 << (kN + kN)];
int ord[2 * kN * kS], stds[50], ults[50], n, s;

int Dfs(int k, int s0, int s1, int u) {
	if (k == 2 * n * (s + 1)) return 0;
	if (vis[s0][s1][u]) return dp[s0][s1][u];
	vis[s0][s1][u] = true;
	int id = ord[k], ss = s0 + s1, uu = __builtin_popcount(u), m = (id <= n ? 1 : -1);
	auto &ans = dp[s0][s1][u] = -1e9 * m;
	auto cmp = id <= n ? [](int x, int y) { return max(x, y); } : [](int x, int y) { return min(x, y); };
	if (max(s0 + (id <= n), s1 + (id > n)) <= n * s) {
		ans = cmp(ans, m * stds[ss] + Dfs(k + 1, s0 + (id <= n), s1 + (id > n), u));
	}
	if (~u & (1 << id)) {
		ans = cmp(ans, m * ults[uu] + Dfs(k + 1, s0, s1, u | (1 << id)));
	}
	return ans;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> n >> s;
	int cnt = 2 * n * (s + 1);
	for (int i = 0; i < cnt; i++) cin >> ord[i];
	int ps; cin >> ps;
	for (int i = 0; i < ps; i++) cin >> stds[i];
	sort(stds, stds + ps, greater<int>());
	int pu; cin >> pu;
	for (int i = 0; i < pu; i++) cin >> ults[i];
	sort(ults, ults + pu, greater<int>());
	cout << Dfs(0, 0, 0, 0) << '\n';
} 
