#include <bits/stdc++.h>
using namespace std;
const int kN = 5e5 + 10;

int n, m;
int a[kN];
vector<int> g[kN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	for(int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	for(int i = 1; i <= n; i++) if(!a[i]) {
		bool flag = 1;
		for(int j : g[i])
			if(a[j] != 1) {flag = 0; break;}
		if(flag) return printf("%d\n", i), 0;
	}
	return 0;
} 
