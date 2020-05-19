#include <stdio.h>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
#define F first
#define S second
#define PB push_back

constexpr int kN = int(1E3 + 10), kInf = int(1E9 + 10);

vector<pair<int, int>> graph[kN];
int cost[kN][kN], x[kN], y[kN], c[kN];

int dist(int x1, int y1, int x2, int y2) {
	int x = x1 - x2, y = y1 - y2;
	return int(ceil(sqrt(x * x + y * y)));
}

int main() {
	int x1, y1, x2, y2, b, c0, k, t, ans = kInf, u, v, n, tmp;
	scanf("%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &b, &c0, &t);
	for (int i = 1; i <= t; i++) scanf("%d", &c[i]);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &x[i], &y[i], &k);
		for (int j = 1; j <= k; j++) {
			scanf("%d%d", &u, &v);
			u++;
			graph[i].PB({u, v});
			graph[u].PB({i, v});
		}
	}
	
	for (int i = 1; i <= n; i++) for (int j = 0; j <= b; j++) cost[i][j] = kInf;
	for (int i = 1; i <= n; i++) {
		tmp = dist(x1, y1, x[i], y[i]);
		if (tmp <= b) cost[i][tmp] = tmp * c0;
	}
	for (int i = 1; i <= b; i++) {	
		for (int j = 1; j <= n; j++) {
			for (pair<int, int> edge : graph[j]) {
				tmp = dist(x[edge.F], y[edge.F], x[j], y[j]);
				if (tmp + i <= b) cost[edge.F][tmp + i] = min(cost[edge.F][tmp + i], cost[j][i] + tmp * c[edge.S]);
			}
		}
	}

	for (int i = 1; i <= n; i++) for (int j = 0; j <= b; j++) {
		if (dist(x2, y2, x[i], y[i]) + j <= b) {
			ans = min(ans, cost[i][j] + dist(x2, y2, x[i], y[i]) * c0);
		}
	}
	if (dist(x1, y1, x2, y2) <= b) {
		ans = min(ans, c0 * dist(x1, y1, x2, y2));
		printf("%d\n", ans);
	}
	else printf("-1\n");
} 
