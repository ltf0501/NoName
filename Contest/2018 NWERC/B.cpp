#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back

constexpr int kN = int(4E5 + 10), kInf = int(1E9 + 10);

bool went[kN];
int a[kN], sz[kN], d[kN], n, val[kN], nsz[kN];
vector<int> graph[kN], ng[kN];

void dfs(int pos) {	
	went[pos] = true;
	vector<int> tmp;
	for (int i : ng[pos]) if (!went[i]) dfs(i);
	for (int i : ng[pos]) tmp.PB(val[i]);
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < nsz[pos]; i++) val[pos] = min(val[pos], tmp[i] - i - 1);
	return ;
}

int ok() {
	int now = 0, cur, x = kInf, ans = kInf;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	for (int i = 1; i <= n; i++) val[i] = x - a[i];
	for (int i = 1; i <= n; i++) went[i] = false;
	for (int i = 1; i <= n; i++) if (!went[i]) dfs(i);
	for (int i = 1; i <= n; i++) d[i] = sz[i];
	for (int i = 1; i <= n; i++) if (d[i] == 0) pq.push({val[i], i});
	//printf("x = %d\n", x);
	//for (int i = 1; i <= n; i++) printf("val[%d] = %d\n", i, val[i]);
	while (!pq.empty()) {
		cur = pq.top().S;
		pq.pop();
		//printf("cur = %d, now = %d\n", cur, now);
		ans = min(ans, val[cur] - now);
		now++;
		for (int i = 0; i < nsz[cur]; i++) {
			if (--d[ng[cur][i]] == 0) pq.push({val[ng[cur][i]], ng[cur][i]});
		}
	}
	return x - ans;
}


int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i], &sz[i]);
		graph[i].resize(sz[i]);
		for (int j = 0; j < sz[i]; j++) scanf("%d", &graph[i][j]);
	}
	for (int i = 1; i <= n; i++) for (int j : graph[i]) ng[j].PB(i);
	for (int i = 1; i <= n; i++) nsz[i] = int(ng[i].size());
	printf("%d\n", ok());
} 
