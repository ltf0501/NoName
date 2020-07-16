#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 3e5 + 10;
const ll kInf = 1e16;
typedef pair<int, int> pii;
#define F first
#define S second

int n, m;
vector<pii> g[kN];
bool check[kN];
int from[kN];

ll dis[kN];
bool vis[kN];
struct Edge {
	int x, y, w;
};
vector<Edge> edges;
ll ans[kN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int x, y, w; scanf("%d%d%d", &x, &y, &w);
		g[x].emplace_back(y, w), g[y].emplace_back(x, w);
		edges.push_back({x, y, w});
	}

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	for(int i = 1; i <= n; i++) dis[i] = kInf;
	int T; scanf("%d", &T);
	vector<int> v;
	while(T--) {
		int x; scanf("%d", &x);
		v.push_back(x);
		dis[x] = 0, from[x] = x;
		pq.emplace(0, x);
	}

	while(!pq.empty()) {
		auto t = pq.top(); pq.pop();
		ll d = t.F;
		int u = t.S;
		if(vis[u]) continue;
		vis[u] = 1;

		for(auto e : g[u]) {
			int v = e.F, w = e.S;
			if(dis[v] > d + w || (dis[v] == d + w && from[v] > from[u])) {
				dis[v] = d + w;
				from[v] = from[u];
				pq.emplace(dis[v], v);
			}
		}
	}

//	for(int i = 1; i <= n; i++) {
//		printf("%d: dis = %lld, from = %d\n", i, dis[i], from[i]);
//	}
	for(auto e : edges) {
		ll delta = dis[e.x] - dis[e.y];
		int xx = from[e.x], yy = from[e.y];
		//printf("delta = %lld\n", delta);
		ans[xx] += e.w - delta;
		ans[yy] += e.w + delta;
	}

	for(int x : v) {
		printf("%lld", ans[x] >> 1);
		if(ans[x] & 1) puts(".5");
		else puts(".0");
	}
	return 0;
} 
