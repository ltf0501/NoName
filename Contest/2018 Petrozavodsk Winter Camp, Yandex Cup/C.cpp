#include <stdio.h>
#include <bitset>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(1E3 + 10);
vector<int> graph[kN], ng[kN];
int tox[kN], toy[kN];
bool left[kN];
bitset<kN> went, connected;

bool dfs(int pos) {
	went[pos] = true;
	for (int i : ng[pos]) if (!connected[i]) {
		toy[pos] = i;
		tox[i] = pos;
		connected[i] = true;
		return true;
	}
	for (int i : ng[pos]) if (!went[tox[i]] && dfs(tox[i])) {
		tox[i] = pos;
		toy[pos] = i;
		return true;
	}
	return false;
}


bool ok(int pos, int n) {
	for (int i = 1; i <= n; i++) ng[i].clear();
	for (int i = 1; i <= n; i++) left[i] = false;
	for (int i : graph[pos]) left[i] = true;
	for (int i = 1; i <= n; i++) if (i != pos && left[i]) for (int j : graph[i]) if (j != pos && !left[j]) {
		ng[i].PB(j);
		ng[j].PB(i);
	}
	connected.reset();
	for (int i = 1; i <= n; i++) if (i != pos && !left[i]) {
		went.reset();
		if (!dfs(i)) return false;
	}
	return true;
}

int main() {
	int n, m, l, r;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	for (int i = 1; i <= n; i++) if (graph[i].size() >= ((n - 1) >> 1)) {
		if (ok(i, n)) {
			printf("Yes\n%d %d\n", i, int(graph[i].size()));
			went.reset();
			for (int j = 1; j <= n; j++) if (j != i) {
				if (!left[j]) {
						printf("%d %d\n", j, toy[j]);
						went[j] = went[toy[j]] = true;
				}
			}
			for (int j = 1; j <= n; j++) if (j != i) if (!went[j]) printf("%d -1\n", j);
			return 0;
		}
	}
	printf("No\n");
} 
