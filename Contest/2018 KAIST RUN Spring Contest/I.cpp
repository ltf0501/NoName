#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(1E6 + 10);
constexpr int kInf = int(1E9 + 10);

struct Routes {
	pair<int, int> p[4]; // {distance, from}
	Routes() {
		for (int i = 0; i < 4; i++) p[i] = {kInf, -1};
	}
	void add(int a, int b) {
		p[0] = {b, a};
		sort(p, p + 4);
		p[3] = p[2];
		p[2] = p[1];
		p[1] = p[0];
		return ;
	}
};


// 1 -> A -> B - C <- D <- n
vector<pair<int, int>> graph[kN];
Routes AB[kN], DC[kN];
int from_S[kN], from_T[kN];

void addedge(int u, int v, int x) {
	graph[u].PB({v, x});
	graph[v].PB({u, x});
	return ;
}

int Distance(int u, int v, int s, int t) {
	int ans = kInf;
	vector<int> ve;
	for (int i = 1; i <= 3; i++) if (AB[u].p[i].S != -1) 
		for (int j = 1; j <= 3; j++) if (DC[v].p[j].S != -1) {
			ve.clear();
			ve.PB(u), ve.PB(v), ve.PB(AB[u].p[i].S), ve.PB(DC[v].p[j].S);
			sort(ve.begin(), ve.end());
			ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
			if (ve.size() == 4) ans = min(ans, AB[u].p[i].F + DC[v].p[j].F);
		}
	return ans;
}

int main() {
	int n, m, k, l, r, x, s = 1, t, ans = kInf;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &l, &r, &x);
		addedge(l, r, x);
	}
	for (int i = 1; i <= 5 - k; i++) {
		n++;
		addedge(n - 1, n, 0);
	}
	t = n;
	for (int i = 1; i <= n; i++) from_S[i] = from_T[i] = kInf;
	for (pair<int, int> i : graph[s]) from_S[i.F] = i.S;
	for (pair<int, int> i : graph[t]) from_T[i.F] = i.S;
	for (int i = 1; i <= n; i++) if (i != s && i != t) 
		for (pair<int, int> j : graph[i]) if (j.F != s && j.F != t) {	
			AB[j.F].add(i, j.S + from_S[i]);
			DC[j.F].add(i, j.S + from_T[i]);
		}
	for (int i = 1; i <= n; i++) if (i != s && i != t) 
		for (pair<int, int> j : graph[i]) if (j.F != s && j.F != t) 
			ans = min(ans, j.S + Distance(i, j.F, s, t));

	if (ans == kInf) printf("-1\n");
	else printf("%d\n", ans);
} 
