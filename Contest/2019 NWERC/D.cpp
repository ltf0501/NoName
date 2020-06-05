#include <bits/stdc++.h>
using namespace std;
const int kN = 2e3 + 10;
typedef long long ll;
const ll kInf = 1e16;
typedef pair<int, int> pii;
#define F first
#define S second

vector<pii> g[kN];
int n, m;
ll dp[kN][kN];
bool vis[kN][kN];
bool ans[kN];

ll cal(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
	return ax * by + bx * cy + cx * ay - ay * bx - by * cx - cy * ax;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y, w; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &w);
		g[x].emplace_back(y, w), g[y].emplace_back(x, w);
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= n; j++) dp[i][j] = kInf;
	}
	dp[1][0] = 0;
	for(int j = 1; j <= n; j++) {
		for(int u = 1; u <= n; u++) {
			for(auto v : g[u]) {
				dp[u][j] = min(dp[u][j], dp[v.F][j - 1] + v.S);
			}
		}
	}

	vector<int> s;
	queue<pii> q;

	ll mn = kInf - 1;
	for(int i = 0; i <= n; i++) {
		if(dp[n][i] > mn) continue;
		mn = min(mn, dp[n][i]);
		int sz = s.size();
		// (s[sz - 2], dp[n][s[sz - 2]]), (s[sz - 1], dp[n][s[sz - 1]]), (i, dp[n][i])
		while(sz >= 2 && cal(s[sz - 2], dp[n][s[sz - 2]], s[sz - 1], dp[n][s[sz - 1]], i, dp[n][i]) < 0) s.pop_back(), sz--;
		s.push_back(i);
	}

	for(int i : s) {
		vis[n][i] = 1;
		q.emplace(n, i);
	}

	while(!q.empty()) {
		auto t = q.front(); q.pop();
		int u = t.F, step = t.S;
		ans[u] = 1;
		for(auto v : g[u]) {
			if(step && vis[v.F][step - 1] == 0 && dp[u][step] == dp[v.F][step - 1] + v.S) {
				vis[v.F][step - 1] = 1;
				q.emplace(v.F, step - 1);
			}
		}
	}

	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += !ans[i];
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if(!ans[i]) printf("%d ", i); puts("");
	return 0;
}
