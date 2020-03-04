#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 2.5e5 + 10;
const int kInf = 1e9;
struct P {
	int l, r, w;
	bool operator < (const P & t) const {
		if(l != t.l) return l < t.l;
		return r > t.r;
	}
};

int n;
P a[kN];
vector<int> g[kN];
multiset<ll, greater<ll>> st[kN];
ll ans[kN];
void dfs(int u) {
	for(int v : g[u]) {
		dfs(v);
		if(st[u].size() < st[v].size()) st[u].swap(st[v]);
		multiset<ll, greater<ll>> tmp;
		for(auto it : st[v]) {
			ll k = *st[u].begin();
			st[u].erase(st[u].begin());
			tmp.insert(k + it);
		}
		for(auto it : tmp) st[u].insert(it);
	}
	if(u) st[u].insert(a[u].w);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].w);
	a[0] = {-kInf, kInf, 0};
	sort(a, a + n + 1); 
	stack<int> s;
	s.push(0);
	for(int i = 1; i <= n; i++) {
		while(a[s.top()].r < a[i].r) s.pop();
		g[s.top()].push_back(i);
		s.push(i);
	}
	dfs(0);
	int i = 0;
	for(auto it : st[0]) {
		ans[i++] = it;
	}
	for(int i = 1; i < n; i++) ans[i] += ans[i - 1];
	for(int i = 0; i < n; i++) printf("%lld ", ans[i]); puts("");
	return 0;
}
