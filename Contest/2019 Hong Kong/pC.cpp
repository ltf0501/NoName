#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define F first
#define S second
const int kN = 4e5 + 10;
 
vector<int> g[kN];
ll a[kN];
int n;
bool vis[kN];
int sz[kN], mx[kN];
ll sum[kN], mx_val[kN];
vector<int> now;
int bit[kN];
ll ans;
void add(int x, int m, int d) {
	for(int i = x; i <= m; i += (i & -i)) bit[i] += d;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= (i & -i)) res += bit[i];
	return res;
}
 
void get_cen(int u) {
	now.push_back(u);
	sz[u] = 1, mx[u] = 0, vis[u] = 1;
	for(int v : g[u]) if(!vis[v]) {
		get_cen(v);
		sz[u] += sz[v], mx[u] = max(mx[u], sz[v]);
	}
}
void get_dis(int u, ll d, ll mxx) {
	now.push_back(u);
	vis[u] = 1;
	sum[u] = a[u] + d;
	mx_val[u] =	max(a[u], mxx);
	for(int v : g[u]) if(!vis[v]) {
		get_dis(v, sum[u], mx_val[u]);
	}
}
void dfs(int u) {
	int cen = -1;
	now.clear();
	get_cen(u);
	int s = int(now.size());
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
		vis[w] = 0;
	}
	//printf("cen = %d\n", cen);
	//printf("now: ");
	//for(int x : now) printf("%d ", x); puts("");
	now.clear();
	vector<pll> tmp; // first = mx, second = sum
	vector<ll> v;
	get_dis(cen, 0, 0);
	for(int w : now) tmp.emplace_back(mx_val[w], sum[w]), vis[w] = 0;
	now.clear();
	sort(tmp.begin(), tmp.end());
	for(auto p : tmp) {
		v.push_back(p.S);
		v.push_back(2 * p.F + a[cen] - p.S);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	int m = int(v.size());
	//printf("v: ");
	//for(ll x : v) printf("%lld ", x); puts("");
	vector<int> update;
	for(auto p : tmp) {
		int	id = lower_bound(v.begin(), v.end(), 2 * p.F + a[cen] - p.S) - v.begin() + 1;
		ans += query(m) - query(id);
		int add_id = lower_bound(v.begin(), v.end(), p.S) - v.begin() + 1;
		add(add_id, m, 1);
		update.push_back(add_id);
	}
 
	for(int x : update) add(x, m, -1);
	v.clear();
	tmp.clear();
	update.clear();
 
	vis[cen] = 1;
	for(int son : g[cen]) if(!vis[son]) {
		get_dis(son, a[cen], a[cen]);
 
		for(int w : now) tmp.emplace_back(mx_val[w], sum[w]), vis[w] = 0;
		now.clear();
		sort(tmp.begin(), tmp.end());
		for(auto p : tmp) {
			v.push_back(p.S);
			v.push_back(2 * p.F + a[cen] - p.S);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		m = int(v.size());
 
		for(auto p : tmp) {
			int	id = lower_bound(v.begin(), v.end(), 2 * p.F + a[cen] - p.S) - v.begin() + 1;
			ans -= query(m) - query(id);
			int add_id = lower_bound(v.begin(), v.end(), p.S) - v.begin() + 1;
			add(add_id, m, 1);
			update.push_back(add_id);
		}
 
		for(int x : update) add(x, m, -1);
		v.clear();
		tmp.clear();
		update.clear();
	}
 
	for(int son : g[cen]) 
		if(!vis[son]) dfs(son);
}
void init() {
	for(int i = 1; i <= n; i++) g[i].clear();
	ans = 0;
	for(int i = 1; i <= n; i++) vis[i] = 0;
	now.clear();
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for(int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}
		dfs(1);
		printf("%lld\n", ans);
	}
 
	return 0;
}
