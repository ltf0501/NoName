#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(3E5 + 10), kMod = 998244353, kM = int(5E5 + 10);
int dep[kN], p[kN], u[kM], v[kM];
bool used[kM], went[kN];
vector<int> graph[kN];

ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}

int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}
int dis(int l, int r) {
	int ans = 0;
	if (dep[l] < dep[r]) swap(l, r);
	while (dep[l] > dep[r]) {
		ans++;
		l = p[l];
	}
	while (l != r) {
		l = p[l];
		r = p[r];
		ans += 2;
	}
	return ans;
}
void dfs(int pos, int from) {
	went[pos] = true;
	p[pos] = from;
	dep[pos] = dep[from] + 1;
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	return ;
}

int main() {
	int n, m, tmp, x;
	ll ans = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= m; i++) scanf("%d%d", &u[i], &v[i]);
	for (int i = 1; i <= m; i++) if (Find(u[i]) != Find(v[i])) {
		p[Find(u[i])] = p[Find(v[i])];
		graph[u[i]].PB(v[i]);
		graph[v[i]].PB(u[i]);
		used[i] = true;
	}
	for (int i = 1; i <= n; i++) if (!went[i]) dfs(i, i);
	x = m;
	for (int i = 1; i <= m; i++) if (!used[i]) {
		tmp = dis(u[i], v[i]) + 1;
		x -= tmp;
		ans = ans * (Pow(2, tmp) + kMod - 1) % kMod;
	}
	ans = ans * Pow(2, x) % kMod;
	printf("%lld\n", ans);
} 
