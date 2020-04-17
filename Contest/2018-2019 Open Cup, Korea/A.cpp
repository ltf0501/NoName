#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(2E5 + 10);

vector<int> graph[kN];
int cnt[kN], tot, top[kN], sz[kN], to[kN], dep[kN], p[kN], pc[kN], mm[kN];
map<int, pair<int, int>> m[kN];
void dfs(int pos, int from) {
	to[pos] = 0;
	sz[pos] = 1;
	p[pos] = from;
	dep[pos] = dep[from] + 1;
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	for (int i : graph[pos]) if (i != from) {
		sz[pos] += sz[i];
		if (to[pos] == 0) to[pos] = i;
		else if (sz[i] > sz[to[pos]]) to[pos] = i;
	}
	return ;
}
void init(int pos) {
	for (int i : graph[pos]) if (i != p[pos]) top[i] = i; 
	top[to[pos]] = top[pos];
	for (int i : graph[pos]) if (i != p[pos]) init(i);
	return ;
}
void addcolor(int c, int x) {
	mm[cnt[c]]--;
	cnt[c] += x;
	mm[cnt[c]]++;
	return ;
}

void fix(int l, int c) {
	map<int, pair<int, int>>:: iterator u;
	while (l != 0) {
		while (true) {
			u = m[top[l]].begin();
			if (u != m[top[l]].end() && u->F < dep[l]) {
				if (u->S.F > dep[l]) {
					int tmp = u->S.F, tc = u->S.S;
					addcolor(u->S.S, -(dep[l] - u->F));
					m[top[l]].erase(u);
					m[top[l]].insert({dep[l], {tmp, tc}});
					break;
				}
				else {
					addcolor(u->S.S, -(u->S.F - u->F));
					m[top[l]].erase(u);	
				}
			}
			else break;
		}
		m[top[l]].insert({dep[top[l]], {dep[l], c}});
		addcolor(c, dep[l] - dep[top[l]]);
		if (pc[top[l]]) addcolor(pc[top[l]], -1);
		pc[top[l]] = c;
		addcolor(pc[top[l]], 1);
		l = p[top[l]];
	}
	return ;
}

int main() {
	int n, c, q, l, r;
	scanf("%d%d%d", &n, &c, &q);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	tot = 0;
	dfs(1, 0);
	top[1] = 1;
	init(1);
	mm[0] = c;

	while (q--) {
		scanf("%d%d%d", &l, &r, &c);
		fix(l, r);
		addcolor(pc[1], -1);
		pc[1] = 0;
		printf("%d\n", mm[c]);
	}
}
