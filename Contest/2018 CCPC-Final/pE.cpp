#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int kN = 1e5 + 10, kM = int(2E5 + 10), kK = int(1E3 + 10);
constexpr ll kInf = ll(1E16 + 10);
typedef pair<int, int> pii;
#define F first
#define S second
#define PB push_back
int n, m, k;
struct Edge {
	int x, y, w;
};
vector<Edge> edges;
vector<int> g[kN], ng[kN];
int to(int x, int id) {return x ^ edges[id].x ^ edges[id].y;}

stack<pair<pair<int, int>, int>> s;
vector<vector<pair<ll, int>>> cycle;
vector<pair<ll, int>> emp;
ll dp[kK][2];
short from[kN][kK];
int pos[kM], p[kN], dep[kN];
bool used[kM], killed[kM], went[kN];

int Find(int n) {return p[n] == n ? n : p[n] = Find(p[n]);}
bool Merge(int l, int r) {
	l = Find(l), r = Find(r);
	if (l == r) return false;
	p[Find(l)] = Find(r);
	return true;
} 

void dfs(int pos) {
	went[pos] = true;
	int nxt;
	for (int i : ng[pos]) {
		nxt = to(pos, i);
		if (!went[nxt]) {
			dep[nxt] = dep[pos] + 1;
			p[nxt] = i;
			dfs(nxt);
		}
	}
	return ;
}

void LCA(int id) {
	int l = edges[id].x, r = edges[id].y;
	emp.clear();
	emp.PB({edges[id].w, id});
	if (dep[l] > dep[r]) swap(l, r);
	while (dep[l] < dep[r]) {
		emp.PB({edges[p[r]].w, p[r]});
		r = to(r, p[r]);
	}

	while (l != r) {
		emp.PB({edges[p[l]].w, p[l]});
		emp.PB({edges[p[r]].w, p[r]});
		l = to(l, p[l]);
		r = to(r, p[r]);
	}

	sort(emp.begin(), emp.end());
	cycle.PB(emp);
	return ;
}

void pre() {
	cycle.clear();
	for (int i = 1; i <= n; i++) ng[i].clear();

	for (int i = 0; i < m; i++) if (used[i]) {
		ng[edges[i].x].PB(i);
		ng[edges[i].y].PB(i);
	}

	memset(went, false, sizeof(went));
	for (int i = 1; i <= n; i++) if (!went[i]) {
		dep[i] = 0;
		dfs(i);
	}

	for (int i = 0; i < m; i++) if (!used[i]) LCA(i);
	return ;
}

void solve() {
	int sz, cnt, now = 1, ni, ork;
	short nj;
	bool f;
	scanf("%d%d%d", &n, &m, &k);
	edges.resize(m + 1);
	for(int i = 0; i < m; i++) scanf("%d%d%d", &edges[i].x, &edges[i].y, &edges[i].w);
	
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 0; i < m; i++) used[i] = Merge(edges[i].x, edges[i].y);

	cnt = 0;
	for (int i = 1; i <= n; i++) if (p[i] == i) cnt++;
	ork = k;
	if (k <= cnt) {
		for (int i = 1; i <= n; i++) if (p[i] == i) {
			if (k > 0) pos[i] = k--;
			else pos[i] = 1;
		}
		printf("0\n");
		for (int i = 1; i < n; i++) printf("%d ", pos[Find(i)]);
		printf("%d\n", pos[Find(n)]);
	}
	else {
		k -= cnt;
		
		pre();

		for (int i = 1; i <= k; i++) dp[i][!f] = kInf;
		dp[0][!f] = 0;
		memset(used, false, sizeof(used));
		for (vector<pair<ll, int>> i : cycle) for (pair<ll, int> j : i) used[j.S] = true;
		emp.clear();
		for (int i = 0; i < m; i++) if (!used[i]) emp.PB({edges[i].w, i});
		emp.PB({0, m});
		sort(emp.begin(), emp.end());
		cycle.PB(emp);	
		edges[m] = {0, 0, 0};
		
		//printf("cycles :\n"); for (vector<pair<ll, int>> i : cycle) {for (pair<ll, int> j : i) printf("%d ", j.S); printf("\n");}
		
		for (int i = 0; i < int(cycle.size()); i++, f = !f) {
			sz = int(cycle[i].size());
			for (int j = 1; j < sz; j++) cycle[i][j].F += cycle[i][j - 1].F;
			for (int j = 0; j <= k; j++) dp[j][f] = dp[j][!f];
			for (int j = 0; j <= k; j++) from[i][j] = j;
			for (int j = 1; j < sz; j++) for (int x = j; x <= k; x++) {
				if (dp[x][f] > dp[x - j][!f] + cycle[i][j].F) {
					from[i][x] = x - j;
					dp[x][f] = dp[x - j][!f] + cycle[i][j].F;
				}
			}
		}
		ni = int(cycle.size()) - 1;
		nj = k;
		for (int  i = 0; i < m; i++) killed[i] = false;
		while (ni >= 0) {
			if (from[ni][nj] != nj) {
				for (int x = 0; x <= nj - from[ni][nj]; x++) killed[cycle[ni][x].S] = true;
				nj = from[ni][nj];
			}
			ni--;
		}
		for (int i = 1; i <= n; i++) p[i] = i;
		for (int i = 0; i < m; i++) if (!killed[i]) Merge(edges[i].x, edges[i].y);

		for (int i = 1; i <= n; i++) if (p[i] == i) pos[i] = now++;
		printf("%lld\n", dp[k][!f]);
		for (int i = 1; i < n; i++) printf("%d ", pos[Find(i)]);
		printf("%d\n", pos[Find(n)]);
	}
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case %d: ", i);
		solve();
	}
}

