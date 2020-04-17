#include <bits/stdc++.h>
using namespace std;
const int kN = 55;
const int kC = 6e3 + 10;

int n, m;
char Map[kN][kN];
int cur;
int horizontal[kN][kN], vertical[kN][kN];

bool ok(int i, int j) {
	return Map[i][j] == '.' || Map[i][j] == '*' || Map[i][j] == 'O';
}

vector<int> g[kC];
bool vis[kC];
bitset<kC> reach[kC];

void dfs0(int u, int rt) {
	reach[rt][u] = 1;
	vis[u] = 1;
	for(int v : g[u])
		if(!vis[v]) dfs0(v, rt);
}

vector<int> g2[kC];
int in[kC], dfs_clock;
int sccno[kC], scc_cnt;
stack<int> s;

int True(int x) {return x << 1;}
int False(int x) {return x << 1 | 1;}

int dfs(int u) {
	s.push(u);
	int lowu = in[u] = ++dfs_clock;
	for(int v : g2[u]) {
		if(!in[v]) lowu = min(lowu, dfs(v));
		else if(!sccno[v]) lowu = min(lowu, in[v]);
	}

	if(lowu == in[u]) {
		scc_cnt++;
		while(true) {
			int x = s.top(); s.pop();
			sccno[x] = scc_cnt;
			if(x == u) break;
		}
	}
	return lowu;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%s", Map[i] + 1);

	int O = cur++;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(ok(i, j)) {
				if(ok(i, j - 1)) horizontal[i][j] = horizontal[i][j - 1];
				else horizontal[i][j] = cur++;
			}
		}
	}
	for(int j = 1; j <= m; j++) {
		for(int i = 1; i <= n; i++) {
			if(ok(i, j)) {
				if(ok(i - 1, j)) vertical[i][j] = vertical[i - 1][j];
				else vertical[i][j] = cur++;
			}
		}
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(ok(i, j)) {
				if(!ok(i, j - 1) || !ok(i, j + 1)) {
					g[horizontal[i][j]].push_back(vertical[i][j]);
				}
				if(!ok(i - 1, j) || !ok(i + 1, j)) {
					g[vertical[i][j]].push_back(horizontal[i][j]);
				}
				if(Map[i][j] == 'O') {
					g[O].push_back(horizontal[i][j]);
					g[O].push_back(vertical[i][j]);
				}
			}
		}
	}

	for(int i = 0; i < cur; i++) {
		for(int j = 0; j < cur; j++) vis[j] = 0;
		dfs0(i, i);
	}

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(Map[i][j] == '*') {
				g2[False(horizontal[i][j])].push_back(True(vertical[i][j]));
				g2[False(vertical[i][j])].push_back(True(horizontal[i][j]));
			}
		}
	}

	for(int i = 1; i < cur; i++) {
		if(!reach[0][i]) g2[True(i)].push_back(False(i));
	}

	for(int i = 1; i < cur; i++) {
		for(int j = i + 1; j < cur; j++) {
			if(!reach[i][j] && !reach[j][i]) {
				g2[True(i)].push_back(False(j));
				g2[True(j)].push_back(False(i));
			}
		}
	}

	for(int i = 0; i < cur * 2; i++)
		if(!in[i]) dfs(i);

	for(int i = 1; i < cur; i++)
		if(sccno[True(i)] == sccno[False(i)]) return puts("No"), 0;
	puts("Yes");
	return 0;
}
