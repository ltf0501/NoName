#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(3E5 + 10);
constexpr ll kInf = ll(1E12 + 10);

vector<pair<int, int>> graph[kN];
ll dp[kN][2], cnt[kN][2];

void dfs(int pos, int from, ll m) {
	for (pair<int, int> i : graph[pos]) if (i.F != from) dfs(i.F, pos, m);
	int lpos = 0;
	ll val = 0;
	dp[pos][0] = cnt[pos][0] = 0;
	for (pair<int, int> i : graph[pos]) if (i.F != from) {
		dp[pos][0] += dp[i.F][1];
		cnt[pos][0] += cnt[i.F][1];
		if (lpos == 0) {
			lpos = i.F;
			val = dp[i.F][0] - dp[i.F][1] + i.S - m;
		}
		else if (val < dp[i.F][0] - dp[i.F][1] + i.S - m) {
			val = dp[i.F][0] - dp[i.F][1] + i.S - m;
			lpos = i.F;
		}
		else if (val == dp[i.F][0] - dp[i.F][1] + i.S - m) {
			if (cnt[i.F][0] - cnt[i.F][1] < cnt[lpos][0] - cnt[lpos][1]) lpos = i.F;
		}
	}
	if (lpos == 0 || val < 0) {
		dp[pos][1] = dp[pos][0];
		cnt[pos][1] = cnt[pos][0];
	}
	else {
		dp[pos][1] = dp[pos][0] + val;
		cnt[pos][1] = cnt[pos][0] + cnt[lpos][0] - cnt[lpos][1] + 1;
	}
	return ;
}

int main() {
	int n, k;
	ll l, r, mid;
	scanf("%d%d", &n, &k);
	for (int i = 1; i < n; i++) {
		scanf("%lld%lld%lld", &l, &r, &mid);
		graph[l].PB({r, mid});
		graph[r].PB({l, mid});
	}
	dfs(1, 1, -kInf);
	if (cnt[1][1] < k) {
		printf("Impossible\n");
		return 0;
	}
	l = -kInf, r = kInf;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		dfs(1, 1, mid);
		if (cnt[1][1] < k) r = mid;
		else l = mid;
	}
	dfs(1, 1, l);
	printf("%lld\n", dp[1][1] + ll(k) * l);
}
