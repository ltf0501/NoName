#include <stdio.h>
#include <tuple>
#include <vector>
#include <queue>
using namespace std;
#define PB push_back

constexpr int kN = int(1E2 + 10);

int idx[kN][kN][2], deg[kN * kN * 2];
tuple<int, int, int> p[kN * kN * 2];
vector<int> graph[kN * kN * 2], ng[kN * kN * 2];
bool went[kN * kN * 2];

void solve() {
	int n, m, now = 0, l, r, x, y, nxt;
	queue<int> q;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 0; k < 2; k++) 
		idx[i][j][k] = ++now;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 0; k < 2; k++)
		p[idx[i][j][k]] = {i, j, k};

	// 0 -> A's turn / 1 -> B's turn
	for (int i = 1; i <= now; i++) graph[i].clear();
	for (int i = 1; i <= now; i++) ng[i].clear();
	for (int i = 1; i <= now; i++) went[i] = false;

	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		for (int j = 1; j <= n; j++) graph[idx[l][j][0]].PB(idx[r][j][1]);
		for (int j = 1; j <= n; j++) graph[idx[j][l][1]].PB(idx[j][r][0]); 
		for (int j = 1; j <= n; j++) ng[idx[r][j][1]].PB(idx[l][j][0]);
		for (int j = 1; j <= n; j++) ng[idx[j][r][0]].PB(idx[j][l][1]);
	}
	scanf("%d%d", &y, &x);

	for (int i = 1; i <= now; i++) deg[i] = int(graph[i].size());

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i == j) {
		q.push(idx[i][j][0]);
		q.push(idx[i][j][1]);
		went[idx[i][j][0]] = went[idx[i][j][1]] = true;
	}

	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (deg[idx[i][j][1]] == 0) {
		q.push(idx[i][j][1]);
		went[idx[i][j][1]] = true;
	}

	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		//printf("nxt = (%d, %d, %d)\n", get<0>(p[nxt]), get<1>(p[nxt]), get<2>(p[nxt]));
		
		for (int i : ng[nxt]) if (!went[i]) {
			deg[i]--;
			if (get<2>(p[i]) == 0) {
				went[i] = true;
				q.push(i);
			}
			else if (deg[i] == 0) {
				went[i] = true;
				q.push(i);
			}
		}
	}

	if (!went[idx[x][y][1]]) printf("Yes\n");
	else printf("No\n");
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: ", i);
		solve();
	}
} 
