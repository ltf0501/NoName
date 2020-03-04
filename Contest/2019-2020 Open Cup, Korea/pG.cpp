#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(1E5 + 10);
vector<pair<int, int>> graph[kN];
vector<int> ng[kN], ans;
bool can[kN], went[kN];
int t;
bool dfs(int pos) {
	if (pos == t) return true;
	if (went[pos]) return false;
	went[pos] = true;
	sort(graph[pos].begin(), graph[pos].end());
	for (pair<int, int> i : graph[pos]) if (can[i.S]) {
		if (dfs(i.S)) {
			ans.PB(i.F);
			return true;
		}
		else return false;
	}
	return false;
}
void ddfs(int pos) {
	can[pos] = true;
	for (int i : ng[pos]) if (!can[i]) ddfs(i);
	return ;
}
int main() {
	int n, m, s, u, v, c;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &c);
		graph[u].PB({c, v});
		ng[v].PB(u);
	}
	ddfs(t);
	if (!can[s]) printf("IMPOSSIBLE\n");
	else {
		if (dfs(s)) {
			reverse(ans.begin(), ans.end());
			for (int i = 0; i < int(ans.size()) - 1; i++) printf("%d ", ans[i]);
			printf("%d\n", ans.back());
		}
		else printf("TOO LONG\n");
	}
}
