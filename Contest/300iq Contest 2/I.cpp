#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

int n;
vector<int> g[kN];
bool query(int x, const vector<int> &v) {
	printf("? %d %d ", int(v.size()), x);
	for(int i = 0; i < int(v.size()); i++) printf("%d%c", v[i], i == int(v.size()) - 1 ? '\n' : ' ');
	fflush(stdout);
	int a; scanf("%d", &a);
	return a;
}
void answer(int u) {
	printf("! %d\n", u);
	fflush(stdout);
	exit(0);
}

bool vis[kN];
vector<int> now;
int sz[kN], mx[kN];
void get_cen(int u) {
	vis[u] = 1, now.push_back(u);
	sz[u] = 1, mx[u] = 0;
	for(int v : g[u]) if(!vis[v]) {
		get_cen(v);
		sz[u] += sz[v]; mx[u] = max(mx[u], sz[v]);
	}
}
void dfs(int u) {
	int cen = -1;
	get_cen(u);
	int s = now.size();
	if(s == 1) {
		answer(u);
	}
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
		vis[w] = 0;
	}
	//fprintf(stderr, "cen = %d\n", cen);
	now.clear();

	get_cen(cen);
	for(int w : now) vis[w] = 0;
	now.clear();

	vector<int> tmp;
	for(int v : g[cen])
		if(!vis[v]) tmp.push_back(v);
	sort(tmp.begin(), tmp.end(), [&](int x, int y) {return sz[x] > sz[y];});

	vector<int> can;
	int tot = 0;
	int cnt = 0;
	for(int x : tmp) {
		if((tot + sz[x]) * 2 > s) break;
		cnt++;
		can.push_back(x);
		tot += sz[x];
	}
	bool q = query(cen, can);
	if(q) {
		for(int i = 0; i < cnt; i++) vis[tmp[i]] = 1;
	}
	else {
		for(int i = cnt; i < int(tmp.size()); i++) vis[tmp[i]] = 1;
	}
	dfs(cen);
}
int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1);
	return 0;
}
