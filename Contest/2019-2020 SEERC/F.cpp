#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(1E5 + 10);
int tot[kN];
vector<int> graph[kN];

void dfs(int pos, int from) {
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	for (int i : graph[pos]) if (i != from) tot[pos] += tot[i];
	if (tot[pos]) tot[pos]--;
	else tot[pos]++;
	return ;
}

int main() {
	int n, l, r;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	dfs(1, 1);
	if (!tot[1]) printf("Bob\n");
	else printf("Alice\n");
} 
