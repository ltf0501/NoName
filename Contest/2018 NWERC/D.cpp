#include <stdio.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back

typedef long long int ll;
constexpr int kN = int(1E5 + 10);
constexpr ll kInf = ll(1E16 + 10);

ll a, b, d1[kN], dd[kN], dn[kN];
int n, m;
bool went[kN], done[kN];

vector<pair<ll, ll>> graph[kN], ng[kN], nng[kN];

void dfs(int pos) {
	went[pos] = true;
	dd[pos] = 0;
	for (pair<ll, ll> i : nng[pos]) if (!went[i.F]) dfs(i.F);
	else if (!done[i.F]) dd[pos] = kInf;
	for (pair<ll, ll> i : nng[pos]) dd[pos] = max(dd[pos], i.S + dd[i.F]);
	dd[pos] = min(dd[pos], kInf);
	done[pos] = true;
	return ;
}

bool ok(ll x) {
	if (d1[n] <= x) return true;
	for (int i = 1; i <= n; i++) nng[i].clear();
	for (int i = 1; i <= n; i++) went[i] = done[i] = false;
	for (int i = 1; i <= n; i++) for (pair<ll, ll> j : graph[i]) {
		if (j.S + dn[j.F] <= x) {
			nng[i].PB({j.F, j.S});
		}
	}
	for (int i = 1; i <= n; i++) if (!went[i]) dfs(i);
	for (int i = 1; i <= n; i++) if (x + a - dn[i] >= max(b - dd[i], d1[i])) return true;
	return false;
}

int main() {
	int u, v, c;
	ll l, r, mid;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	pair<ll, int> cur;
	scanf("%lld%lld%d%d", &a, &b, &n, &m);
	for (int i = 1; i <= m; i++) {	
		scanf("%d%d%d", &u, &v, &c);
		graph[u].PB({v, c});
		ng[v].PB({u, c});
	}
	dn[n] = 0;
	for (int i = 1; i < n; i++) dn[i] = kInf;
	pq.push({0, n});
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		if (went[cur.S]) continue;
		went[cur.S] = true;
		for (pair<ll, ll> i : ng[cur.S]) if (i.S + cur.F < dn[i.F]) {
			dn[i.F] = i.S + cur.F;
			pq.push({dn[i.F], i.F});
		}
	}
	for (int i = 1; i <= n; i++) went[i] = false;
	d1[1] = 0;
	for (int i = 2; i <= n; i++) d1[i] = kInf;
	pq.push({0, 1});
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		if (went[cur.S]) continue;
		went[cur.S] = true;
		for (pair<ll, ll> i : graph[cur.S]) if (i.S + cur.F < d1[i.F]) {
			d1[i.F] = i.S + cur.F;
			pq.push({d1[i.F], i.F});
		}
	}
	l = -1, r = kInf;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (ok(mid)) r = mid;
		else l = mid;
	}
	printf("%lld\n", r); 
}

