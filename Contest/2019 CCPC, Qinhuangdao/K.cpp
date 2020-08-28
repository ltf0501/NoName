#include <bits/stdc++.h>
using namespace std;
const int kN = 1e6 + 10;

int n;
vector<int> g[kN];
int deg[kN], len[kN];

void Init(int n) {
	for(int i = 1; i <= n; i++) g[i].clear();
	for(int i = 1; i <= n; i++) deg[i] = len[i] = 0;
}

int Dfs(int u) {
	if(deg[u] > 1) return 0;
	int res = 1;
	for(int v : g[u]) res += Dfs(v); 
	return res;
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		Init(n);
		for(int i = 2; i <= n; i++) {
			int x; scanf("%d", &x);
			deg[x]++;
			g[i].push_back(x);
		}

		for(int i = 1; i <= n; i++) {
			if(deg[i] == 0) {
				len[i] = Dfs(i);
			}
		}

		bool flag = 0;
		for(int i = 1; i <= n; i++) {
			flag |= (len[i] & 1);
		}

		puts(flag ? "Takeru" : "Meiya");
	}

	return 0;
} 
