#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 3e5 + 10;

struct Edge {
	int x, y, d;
	bool operator < (const Edge &r) const {return d > r.d;}
};

vector<Edge> edges;
int n, m;

int p[kN], sz[kN];
ll ans = 0;
int Find(int x) {return p[x] == x ? x : p[x] = Find(p[x]);}
bool Union(int x, int y, int w) {
	x = Find(x), y = Find(y);
	if(x == y) return 0;
	if(sz[x] < sz[y]) swap(x, y);
	ans += 1LL * sz[x] * sz[y] * w;
	p[y] = x, sz[x] += sz[y];
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int x, y, d; scanf("%d%d%d", &x, &y, &d);
		edges.push_back({x, y, d});
	} 
	sort(edges.begin(), edges.end());
	for(int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;

	for(int i = 0, j = 0; i < int(edges.size()); i = j) {
		while(j < int(edges.size()) && edges[j].d == edges[i].d) j++;
		for(int k = i; k < j; k++)
			if(Find(edges[k].x) == Find(edges[k].y)) return puts("-1"), 0;

		for(int k = i; k < j; k++) {
			auto e = edges[k];
			Union(e.x, e.y, e.d);
		}
	}

	ll sum = 0, sum2 = 0;
	for(int i = 1; i <= n; i++) if(p[i] == i) {
		sum += sz[i], sum2 += 1LL * sz[i] * sz[i];
	}
	ans += (sum * sum - sum2) / 2;
	printf("%lld\n", ans); 
	return 0;
} 
