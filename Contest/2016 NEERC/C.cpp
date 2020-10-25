#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = int(1E5 + 10);

int in[kN], t, p[kN]; 
bool td[kN], tp[kN], went[kN];
vector<int> graph[kN], ng[kN], gd[kN], gp[kN];
vector<tuple<int, int, int, int>> ans;

int Find(int n) {return p[n] == n ? n : p[n] = Find(p[n]);}

// 1 -> fa, 2 -> son, 3 -> done, 4 -> cir
void dfs(int pos, int from) {
	in[pos] = ++t;
	went[pos] = true;
	for (int i : graph[pos]) if (!went[i]) {
		ng[pos].PB(i);
		dfs(i, pos);
	}
	else if (i != from) {
		if (in[pos] > in[i]) {
			tp[pos] = true;
			gp[pos].PB(i);
		}
		else {
			td[pos] = true;
			gd[pos].PB(i);
		}
	}
	return ;
}

void go(int pos) {
	//printf("go(%d) :", pos);
	//for (int i : ng[pos]) printf(" %d", i);
	//printf("\n");
	for (int i : ng[pos]) go(i);
	if (td[pos]) {
		for (int i : gd[pos]) ans.PB({1, pos, i, 0});
		for (int i : gd[pos]) p[Find(i)] = pos;
		ans.PB({2, pos, 1, 4});
		ans.PB({0, pos, 4, 3});
		for (int i : ng[pos]) if (tp[i] && Find(i) != pos) ans.PB({1, pos, i, 0});
		ans.PB({2, pos, 1, 4});
		for (int i : ng[pos]) if (!tp[i] && Find(i) != pos) ans.PB({1, pos, i, 0});
		ans.PB({2, pos, 1, 2});
		ans.PB({0, pos, 2, 3});
	}
	else {
		for (int i : ng[pos]) if (tp[i]) ans.PB({1, pos, i, 0});
		ans.PB({2, pos, 1, 4});
		for (int i : ng[pos]) if (!tp[i]) ans.PB({1, pos, i, 0});
		ans.PB({2, pos, 1, 2});
		ans.PB({0, pos, 2, 3});
	}
	for (int i : ng[pos]) p[Find(i)] = pos;
	if (tp[pos]) ans.PB({0, pos, 1, 4});
	else ans.PB({0, pos, 1, 2});
	return ;
}

int main() {
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	int n, m, k, lst, cur;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &k, &lst);
		for (int j = 2; j <= k; j++) {
			scanf("%d", &cur);
			graph[cur].PB(lst);
			graph[lst].PB(cur);
			lst = cur;
		}
	}
	for (int i = 1; i <= n; i++) p[i] = i;
	dfs(1, 1);
	//for (int i = 1; i <= n; i++) printf("%d", tp[i] ? 1 : 0);
	//printf("\n");
	//for (int i = 1; i <= n; i++) printf("%d", td[i] ? 1 : 0);
	//printf("\n");
	go(1);
	printf("%d\n", int(ans.size()));
	for (tuple<int, int, int, int> i : ans) {
		if (get<0>(i) == 0) printf("r %d %d %d\n", get<1>(i), get<2>(i), get<3>(i));
		else if (get<0>(i) == 1) printf("j %d %d\n", get<1>(i), get<2>(i));
		else printf("c %d %d %d\n", get<1>(i), get<2>(i), get<3>(i));
	}
} 
