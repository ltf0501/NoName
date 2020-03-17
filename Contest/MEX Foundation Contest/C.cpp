#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
const int kN = 1e5 + 10;

int n, tot, rt;
vector<int> g[kN];

int anc[20][kN], dis[20][kN];
int level[kN], cnt[kN], near[kN], fa[kN];
ll all_dist[kN], up_dist[kN];
set<pii> st[kN]; // {cnt[son], son}

bool vis[kN];
vector<int> now;
int sz[kN], mx[kN];
void get_cen(int u) {
	vis[u] = 1, now.push_back(u);
	sz[u] = 1, mx[u] = 0;
	for(int v : g[u]) if(!vis[v]) {
		get_cen(v);
		sz[u] += sz[v], mx[u] = max(mx[u], sz[v]);
	}
}
void get_dis(int u, int dep, int d) {
	vis[u] = 1, now.push_back(u);
	dis[dep][u] = d;
	for(int v : g[u]) 
		if(!vis[v]) get_dis(v, dep, d + 1);
}
int dfs(int u, int cen_fa = 0, int dep = 0) {
	get_cen(u);
	int s = now.size();
	int cen = -1;
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
		vis[w] = 0;
	}
	now.clear();
	fa[cen] = cen_fa;

	get_dis(cen, dep, 0);
	for(int w : now) vis[w] = 0;
	now.clear();

	level[cen] = dep;
	vis[cen] = 1;
	for(int v : g[cen]) if(!vis[v]) {
		int child_cen = dfs(v, cen, dep + 1);
		near[child_cen] = v;
		st[cen].insert({0, child_cen});
	}

	return cen;
}

void add(int u, int val) {
	for(int i = level[u]; i >= 0; i--) {
		int now = anc[i][u];
		all_dist[now] += 1LL * dis[i][u] * val;
	}

	for(int i = level[u]; i; i--) {
		int now = anc[i][u], fa = anc[i - 1][u];
		st[fa].erase({cnt[now], now});
		cnt[now] += val;
		st[fa].insert({cnt[now], now});
		up_dist[now] += 1LL *	dis[i - 1][u] * val; 
	}

	tot += val;
	cnt[rt] = tot;
}

ll solve() {
	int cur = rt, dep = 0;	
	vector<pii> more; // (node, sz)
	ll ans = 0;
	while(true) {
		int nxt = -1;
		if(!st[cur].empty()) {
			int v = prev(st[cur].end())->S; 	
			if(cnt[v] > tot / 2) nxt = v;
			map<int, int> mp;
			for(auto p : more) {
				int x = p.F;
				int son = anc[dep + 1][x];
				if(son == 0) continue;
				mp[son] += p.S;
			}
			for(auto p : mp) 
				if(cnt[p.F] + p.S > tot / 2) {nxt = p.F; break;}
		}

		if(nxt == -1) {
			ans += all_dist[cur];
			for(auto p : more)
				ans += 1LL * p.S * dis[dep][p.F];
			return ans;
		}
		else {
			vector<pii> tmp;
			int v = near[nxt];
			int moving = cnt[cur] - cnt[nxt];
			ans += (all_dist[cur] - up_dist[nxt]) + moving;

			for(auto p : more) {
				if(p.F == v) moving += p.S; 
				else if(anc[dep + 1][p.F] == nxt) tmp.push_back(p);
				else {
					moving += p.S;
					ans += 1LL * p.S * (dis[dep][p.F] + 1);
				}
			}
			if(moving) tmp.emplace_back(v, moving);
			more.swap(tmp);
			cur = nxt, dep++;
		}
	}
	assert(false);
}
int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	rt = dfs(1);
	for(int i = 1; i <= n; i++) {
		for(int j = level[i], cur = i; j >= 0; j--, cur = fa[cur]) anc[j][i] = cur;
	}

	int q; scanf("%d", &q);
	while(q--) {
		char op[2]; int u;
		scanf("%s %d", op, &u);
		if(op[0] == '+') add(u, 1);
		else add(u, -1);
		printf("%lld\n", solve());
	}
	return 0;
}
