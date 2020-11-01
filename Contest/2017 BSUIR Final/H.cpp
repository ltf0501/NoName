#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(1E5 + 10), kMod = int(1E9 + 7);
ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}
ll Rev(ll n) {return Pow(n, kMod - 2);}

vector<int> graph[kN];
ll dp[kN], con[kN];
void dfs(int pos, int from) {
	con[pos] = 1;
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	for (int i : graph[pos]) if (i != from) con[pos] = con[pos] * (con[i] + 1) % kMod;
	dp[pos] = con[pos];
	for (int i : graph[pos]) if (i != from) dp[pos] = (dp[pos] + dp[i] * con[pos] % kMod * Rev(con[i] + 1)) % kMod;
	return ;
}

int main() {
	int n, l, r;
	ll cc = 0, dd = 0;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	dfs(1, 1);
	for (int i = 1; i <= n; i++) cc += con[i];
	for (int i = 1; i <= n; i++) dd += dp[i];
	printf("%lld %lld\n", cc % kMod, dd % kMod);
} 
