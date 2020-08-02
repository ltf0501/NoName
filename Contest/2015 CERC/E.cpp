#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(3E5 + 10);
#define F first
#define S second
tuple<int, int, int> edges[kN];
int deg[kN], p[kN], cnt[kN], sz[kN], cycle;
pair<int, int> v[kN], ans[kN];

int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}
void Merge(int a, int b) {
	a = Find(a), b = Find(b);
	if (a != b) {
		if (cnt[a] == sz[a]) cycle--;
		if (cnt[b] == sz[b]) cycle--;
		p[b] = a;
		cnt[a] += cnt[b];
		sz[a] += sz[b];
		if (cnt[a] == sz[a]) cycle++;
	}
	return ;
}

int main() {
	int n, m, l, r, c, q, idx = 1, nn = 0, nm = 0; 
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &l, &r, &c);
		edges[i] = {-c, l, r};
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) scanf("%d", &v[i].F);
	for (int i = 1; i <= q; i++) v[i].F = -v[i].F;
	for (int i = 1; i <= q; i++) v[i].S = i;
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= n; i++) sz[i] = 1;
	sort(edges + 1, edges + m + 1);
	sort(v + 1, v + q + 1);
	function<void(int, int)> addedge = [&](int a, int b) {
		//printf("addedge(%d, %d)\n", a, b);
		nm++;
		if (deg[b] == 0) nn++;
		else if (deg[b] == 1) {
			nn--, nm--;
			if (cnt[Find(b)] == sz[Find(b)]) cycle--;
			cnt[Find(b)]++;
			if (cnt[Find(b)] == sz[Find(b)]) cycle++;
		}
		else if (deg[b] == 2) {
			nn++, nm++;
			if (cnt[Find(b)] == sz[Find(b)]) cycle--;
			cnt[Find(b)]--;
			if (cnt[Find(b)] == sz[Find(b)]) cycle++;
		}
		if (deg[a] == 0) nn++;
		else if (deg[a] == 1) {
			nn--, nm--;
			if (cnt[Find(a)] == sz[Find(a)]) cycle--;
			cnt[Find(a)]++;
			if (cnt[Find(a)] == sz[Find(a)]) cycle++;
		}
		else if (deg[a] == 2) {
			nn++, nm++;
			if (cnt[Find(a)] == sz[Find(a)]) cycle--;
			cnt[Find(a)]--;
			if (cnt[Find(a)] == sz[Find(a)]) cycle++;
		}
		deg[a]++, deg[b]++;
		Merge(a, b);
		return ;
	};
	for (int i = 1; i <= q; i++) {
		while (idx <= m) {
			if (get<0>(edges[idx]) <= v[i].F) {
				addedge(get<1>(edges[idx]), get<2>(edges[idx]));
				idx++;
			}
			else break;
		}
		//printf("v[%d] = (%d, %d)\n", i, v[i].F, v[i].S); 
		//printf("nn = %d, nm = %d, cycle = %d\n", nn, nm, cycle);
		ans[v[i].S] = {nn + cycle, nm + cycle};
	}

	for (int i = 1; i <= q; i++) printf("%d %d\n", ans[i].F, ans[i].S);
} 
