#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = 1 << 10, kM = 1 << 21;
bitset<kN> bit[kN];
int arr[kN][kN], pos[kN], ans[kN][kN];
bool went[kM], can[kM];
vector<int> graph[kM], ng[kM];

void addedge(int a, int b) {
	graph[a].PB(b);
	return ;
}
stack<int> s;
int in[kM], dfs_clock;
int sccno[kM], scc_cnt;
vector<int> scc[kM];
bool choose[kM];
int dfs(int u) {
	int lowu = in[u] = ++dfs_clock;
	s.push(u);
	for(int v : graph[u]) {
		if(!in[v]) lowu = min(lowu, dfs(v));
		else if(!sccno[v]) lowu = min(lowu, in[v]);
	}
	if(lowu == in[u]) {
		scc_cnt++;
		bool flag = 1;
		while(true) {
			int x = s.top(); s.pop();
			sccno[x] = scc_cnt;
			if(choose[x ^ 1]) flag = 0;
			scc[scc_cnt].push_back(x);
			if(x == u) break;
		}
		if(flag) {
			for(int x : scc[scc_cnt]) choose[x] = 1;
		}
	}
	return lowu;
}

int main() {
	int n, m, k, a, b, x, now = 0;
	bool f;
	bitset<kN> tmp;
	scanf("%d%d%d%d%d", &n, &m, &k, &a, &b);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &arr[i][j]);
	for (int i = 1; i <= n; i++) bit[i].reset();
	for (int i = 1; i <= n; i++) pos[i] = 0;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (arr[i][j] == 0) pos[i] = j;
	

	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (arr[i][j] == a) bit[i][j] = true;
	for (int i = 1; i <= n; i++) if (pos[i]) bit[i][pos[i]] = true;

	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans[i][j] = arr[i][j];

	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (pos[i] || pos[j]) {
		tmp = bit[i] & bit[j];
		x = tmp.count();
		if (pos[i] && pos[j]) {
			if (tmp[pos[i]] && tmp[pos[j]]) {
				if (x >= 3) {
					addedge(i << 1, i << 1 | 1);	
					addedge(j << 1, j << 1 | 1);
				}
			}
			else if (x >= 2) {
				if (tmp[pos[i]]) addedge(i << 1, i << 1 | 1);	
				else if (tmp[pos[j]]) addedge(j << 1, j << 1 | 1);
			}
		}
		else if (x >= 2) {
			if (pos[i]) {
				if (tmp[pos[i]]) addedge(i << 1, i << 1 | 1);
			}
			else if (pos[j]) {
				if (tmp[pos[j]]) addedge(j << 1, j << 1 | 1);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) bit[i].reset();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (arr[i][j] == b) bit[i][j] = true;
	for (int i = 1; i <= n; i++) if (pos[i]) bit[i][pos[i]] = true;

	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (pos[i] || pos[j]) {
		tmp = bit[i] & bit[j];
		x = tmp.count();
		if (pos[i] && pos[j]) {
			if (tmp[pos[i]] && tmp[pos[j]]) {
				if (x >= 3) {
					addedge(i << 1 | 1, i << 1);	
					addedge(j << 1 | 1, j << 1);
				}
			}
			else if (x >= 2) {
				if (tmp[pos[i]]) addedge(i << 1 | 1, i << 1);	
				else if (tmp[pos[j]]) addedge(j << 1 | 1, j << 1);
			}
		}
		else if (x >= 2) {
			if (pos[i]) {
				if (tmp[pos[i]]) addedge(i << 1 | 1, i << 1);
			}
			else if (pos[j]) {
				if (tmp[pos[j]]) addedge(j << 1 | 1, j << 1);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) if (pos[i] && ans[i][pos[i]]) {
		if (ans[i][pos[i]] == a) addedge(i << 1 | 1, i << 1);
		else addedge(i << 1, i << 1 | 1);
	}

	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (pos[i] != 0 && pos[j] != 0) {
		if (arr[i][pos[j]] == arr[j][pos[i]]) {
			if (arr[i][pos[j]] == a) {
				addedge(i << 1, j << 1 | 1);
				addedge(j << 1, i << 1 | 1);
			}
			else if(arr[i][pos[j]] == b) {
				addedge(i << 1 | 1, j << 1);
				addedge(j << 1 | 1, i << 1);
			}
		}
	}

	for (int i = 1; i <= n; i++) if (pos[i]) {
		if (!in[i << 1]) dfs(i << 1);
		if (!in[i << 1 | 1]) dfs(i << 1 | 1);
	}

	for (int i = 1; i <= n; i++) if (pos[i] && sccno[i << 1] == sccno[i << 1 | 1]) {
		printf("No\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) if (pos[i]) {
		if (choose[i << 1]) ans[i][pos[i]] = a;
		else ans[i][pos[i]] = b;
	}

	printf("Yes\n");
	for (int i = 1; i <= n; i++) {
		printf("%d", ans[i][1]);
		for (int j = 2; j <= m; j++) printf(" %d", ans[i][j]);
		printf("\n");
	}
}
/*
hack
8 8
3
1 2
0 2 3 1 3 3 3 3
2 0 2 3 3 3 3 3
3 2 0 2 3 3 3 3
1 3 2 0 2 3 3 3
3 3 3 2 0 2 3 1
3 3 3 3 2 0 2 3
3 3 3 3 3 2 0 2
3 3 3 3 1 3 2 0
*/
