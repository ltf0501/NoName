#include <stdio.h>
#include <vector>
#include <set>
using namespace std;
#define PB push_back

constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);
bool used[kN], have[kN];
vector<int> graph[kN], ans;
set<int> *v[kN];

void dfs1(int pos, int from = 0) {
	for (int i : graph[pos]) if (i != from) dfs1(i, pos);
	int to = pos; 
	for (int i : graph[pos]) if (i != from && v[to]->size() < v[i]->size()) to = i;
	graph[pos].PB(pos);
	
	for (int i : graph[pos]) if (i != from && i != to) {
		for (int j : *v[i]) if (v[to]->find(j) != v[to]->end()) {
			have[pos] = true;
			break;
		}
		else v[to]->insert(j);
		if (have[pos]) break;
	}


	v[pos] = v[to];

	if (have[pos]) v[pos]->clear();

	

	return ;
}


int main() {
	int n, m;
	scanf("%d", &n);
	for (int i = 1, l, r; i < n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}

	for (int i = 1; i <= n; i++) v[i] = new set<int>();

	scanf("%d", &m);
	for (int i = 1, P, l, r; i <= m; i++) {
		scanf("%d%d", &l, &r);
		if (l != r) {
			v[l]->insert(i);
			v[r]->insert(i);
		}
		else have[l] = true;
	}

	dfs1(1);

	for (int i = 1; i <= n; i++) if (have[i]) ans.PB(i);

	printf("%d\n%d", int(ans.size()), ans[0]);
	for (int i = 1; i < int(ans.size()); i++) printf(" %d", ans[i]);
	printf("\n");
} 
