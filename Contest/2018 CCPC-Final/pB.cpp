#include <stdio.h>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(2E5 + 10), kInf = int(1E9 + 10);
pair<int, int> a[kN], nxt[kN];
bool went[kN], color[kN];
vector<int> graph[kN], v;

bool dfs(int pos) {
	v.PB(pos);
	went[pos] = true;
	for (int i : graph[pos]) if (went[i]) {
		if (color[i] == color[pos]) return false;
	}
	else {
		color[i] = !color[pos];
		if (!dfs(i)) return false;
	}
	return true;
}

void solve() {
	int n, m, ans = kInf, l, r;
	pair<int, int> tl, tr, tmp, nnxt;
	priority_queue<pair<int, int>> pq;
	priority_queue<int, vector<int>, greater<int>> lpq, dlpq;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) graph[i].clear();
	for (int i = 1; i <= n; i++) went[i] = false;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].F, &a[i].S);
	
	for (int i = 1; i <= n; i++) if (graph[i].empty()) {
		nxt[i].F = nxt[i].S  = min(a[i].F, a[i].S);
		a[i].F = a[i].S = max(a[i].F, a[i].S);
		pq.push({a[i].S, i});
		lpq.push(a[i].F);
	}
	else if (!went[i]) {
		color[i] = true;
		v.clear();
		if(!dfs(i)) {
			printf("IMPOSSIBLE\n");
			return ;
		}
		else {
			l = a[v[0]].F, r = a[v[0]].F;
			for (int j : v) if (color[j]) l = min(l, a[j].F), r = max(r, a[j].F);
			else l = min(l, a[j].S), r = max(r, a[j].S);
			tl = {l, r};
			l = a[v[0]].S, r = a[v[0]].S;
			for (int j : v) if (!color[j]) l = min(l, a[j].F), r = max(r, a[j].F);
			else l = min(l, a[j].S), r = max(r, a[j].S);
			tr = {l, r};
			if (tl.F < tr.F) {
				a[i] = tr;
				nxt[i] = tl;
			}
			else {
				a[i] = tl;
				nxt[i] = tr;
			}
			pq.push({a[i].S, i});
			lpq.push(a[i].F);
		}
	}
	while (!pq.empty()) {
		while (!dlpq.empty()) {
			if (dlpq.top() == lpq.top()) {
				dlpq.pop();
				lpq.pop();
			}
			else break;
		}
		ans = min(ans, pq.top().F - lpq.top());
		tmp = pq.top();
		pq.pop();
		if (tmp.S > 0) {
			nnxt = nxt[tmp.S];
			if (nnxt.S <= tmp.F) {
				dlpq.push(a[tmp.S].F);
				pq.push({nxt[tmp.S].S, -1});
				lpq.push(nxt[tmp.S].F);
			}
			else {
				printf("%d\n", ans);
				return ;
			}
		}
		else {
			printf("%d\n", ans);
			return ;
		}
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
