#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define F first
#define S second

struct Node {
	int cnt[10];
	Node() {memset(cnt, 0, sizeof(cnt));}
	bool operator < (const Node &b) const {
		for(int i = 0; i < 10; i++) if(cnt[i] != b.cnt[i]) return cnt[i] < b.cnt[i];
		return 0;
	}
	void out() {
		printf("cnt: ");
		for(int i = 0; i < 10; i++) printf("%d ", cnt[i]); puts("");
	}
};
int a[20];
map<Node, pll> dp[20][2];

pll Dfs(int pos, Node state, int keep, int zero) {
	if(pos == -1) return {0, 1};
	if(!keep && dp[pos][zero].count(state)) return dp[pos][zero][state];
	ll ans = 0, sum = 0, num = 0;
	for(int i = 0; i <= (keep ? a[pos] : 9); i++) {
		Node t = state;
		t.cnt[i]++;
		if(zero) t.cnt[0] = 0;
		pll tmp = Dfs(pos - 1, t, keep && i == a[pos], zero && i == 0);

		num += tmp.S;
		ans += tmp.F + tmp.S * sum; 
		sum += state.cnt[i];
	}
	//printf("pos = %d, keep = %d, zero = %d\n", pos, keep, zero);
	//state.out();
	//printf("ans = %lld, num = %lld\n", ans, num);
	if(!keep) dp[pos][zero][state] = {ans, num};
	return {ans, num};
}
ll Cal(ll x) {
	if(!x) return 0;
	int pos = 0;
	while(x) {
		a[pos++] = x % 10, x /= 10;
	}
	//printf("a: ");
	//for(int i = 0; i < pos; i++) printf("%d ", a[i]); puts("");
	return Dfs(pos - 1, Node(), 1, 1).F;
}
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		ll l, r; scanf("%lld%lld", &l, &r);
		ll y = Cal(r);
		ll x = Cal(l - 1);
		printf("Case %d: %lld\n", ++cas, y - x);
		//printf("%lld\n", Cal(r) - Cal(l - 1));
	}
	return 0;
} 
