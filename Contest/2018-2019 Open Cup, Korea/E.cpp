#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;

set<int> s[kN];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		s[x].insert(y), s[y].insert(x);
	}
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(int(s[i].size()) == 2) q.push(i);

	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(int(s[u].size()) != 2) continue;
		//printf("u = %d\n", u);
		int a = *s[u].begin(), b = *next(s[u].begin());
		//printf("a = %d, b = %d\n", a, b);
		s[u].clear();
		s[a].erase(u), s[b].erase(u);
		s[a].insert(b), s[b].insert(a);
		if(int(s[a].size()) == 2) q.push(a);
		if(int(s[b].size()) == 2) q.push(b);
	}

	int cnt = 0;
	bool ok = 1;
	for(int i = 1; i <= n; i++) {
		if(int(s[i].size()) == 1) cnt++;
		else if(int(s[i].size()) >= 2) ok = 0;
	}
	if(cnt == 2 && ok) puts("Yes");
	else puts("No");
	return 0;
}
