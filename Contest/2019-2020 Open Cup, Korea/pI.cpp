#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 505;
const ll kInf = 1e16;

int n, m;
ll dis[kN][kN], edge[kN][kN];
vector<int> ord[kN];
ll Check(int u, int v, int w) {
	ll res = kInf;
	vector<pair<ll, ll>> d(n);
	for(int i = 0; i < n; i++) d[i] = {dis[u][ord[u][i]], dis[v][ord[u][i]]};
	vector<ll> suf(n + 1);
	for(int i = n - 1; i >= 0; i--) suf[i] = max(suf[i + 1], d[i].second);
	for(int i = 0; i < n - 1; i++) {
		ll x = d[i].first, y = suf[i + 1];
		if(abs(x - y) <= w) res = min(res, x + y + w);
	}
	return res;
}
int fa[kN];
void Dijkstra(int u, int n) {
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	vector<ll> d(n + 1, kInf);
	vector<bool> vis(n + 1);
	pq.push({d[u] = 0, u});
	while(!pq.empty()) {
		auto t = pq.top(); pq.pop();
		if(vis[t.second]) continue;
		vis[t.second] = 1;
		//printf("now = %d, dis = %lld\n", t.second, d[t.second]);
		for(int i = 1; i <= n; i++) {
			if(edge[t.second][i] != kInf && d[t.second] + edge[t.second][i] < d[i]) {
				d[i] = d[t.second] + edge[t.second][i];
				fa[i] = t.second;
				pq.push({d[i], i});
			}
		}
	}
}
void Print(int u, int v, int w, ll a, ll b) {
	w <<= 1, a <<= 1, b <<= 1;
	ll t = (b - a + w) / 2;
	//printf("a = %lld, b = %lld, t = %lld\n", a, b, t);
	if(t == 0 || t == w) {
		if(t == w) swap(u, v);
		Dijkstra(u, n);
		for(int i = 1; i <= n; i++) 
			if(i != u) printf("%d %d\n", i, fa[i]);
		return;
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			if(edge[i][j] != kInf) edge[i][j] <<= 1;
	}
	for(int i = 1; i <= n; i++) edge[i][n + 1] = edge[n + 1][i] = kInf;
	edge[u][v] = edge[v][u] = kInf;
	edge[n + 1][u] = edge[u][n + 1] = t;
	edge[n + 1][v] = edge[v][n + 1] = w - t;
	Dijkstra(n + 1, n + 1);
	printf("%d %d\n", u, v);
	for(int i = 1; i <= n; i++)
		if(i != u && i != v) printf("%d %d\n", i, fa[i]);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) dis[i][j] = edge[i][j] = kInf;
		dis[i][i] = 0;
	}
	for(int i = 1; i <= m; i++) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		dis[u][v] = dis[v][u] = edge[u][v] = edge[v][u] = w;
	}
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) ord[i].push_back(j);
		sort(ord[i].begin(), ord[i].end(), [&](int a, int b) {return dis[i][a] < dis[i][b];});
	}

	tuple<int, int, int> can = {-1, -1, -1};
	ll ans = kInf;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) { 
			if(edge[i][j] != kInf) {
				ll tmp = Check(i, j, edge[i][j]); 
				if(tmp < ans) {
					ans = tmp;
					can = make_tuple(i, j, edge[i][j]);
				}
			}
		}
	}

	int u = get<0>(can), v = get<1>(can), w = get<2>(can);
	vector<pair<ll, ll>> d(n);
	for(int i = 0; i < n; i++) d[i] = {dis[u][ord[u][i]], dis[v][ord[u][i]]};
	vector<ll> suf(n + 1);
	for(int i = n - 1; i >= 0; i--) suf[i] = max(suf[i + 1], d[i].second);

	printf("%lld\n", ans);
	for(int i = 0; i < n - 1; i++) {
		ll x = d[i].first, y = suf[i + 1];
		if(abs(x - y) <= w && x + y + w == ans) {
			Print(u, v, w, x, y);
			exit(0);
		}
	}
	return 0;
}
