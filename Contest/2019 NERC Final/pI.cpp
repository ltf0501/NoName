#include <bits/stdc++.h>
using namespace std;
const int kN = 205;
int vis[kN][kN];
int query(int x, int y) {
	if(x == y) return 0;
	if(vis[x][y] != 0) return vis[x][y];
	printf("? %d %d\n", x, y);
	fflush(stdout);
	char c[2];
	scanf("%s", c);
	if(c[0] == '>') {
		vis[x][y] = 1, vis[y][x] = -1;
		return 1;
	}
	else {
		vis[x][y] = -1, vis[y][x] = 1;
		return -1;
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		memset(vis, 0, sizeof(vis));
		int n;
		scanf("%d", &n);
		set<int> a, b;
		for(int i = 1; i <= 2; i++) a.insert(i);
		for(int i = 3; i <= n + 1; i++) b.insert(i);
		for(int i = n + 2; i <= 2 * n + 1; i++) {
			int a_mn = *a.begin();
			for(auto x : a) {
				int res = query(a_mn, x);
				if(res == 0) continue;
				if(res == 1) a_mn = x;
			}	
			int b_mn = *b.begin();
			for(auto x : b) {
				int res = query(b_mn, x);
				if(res == 0) continue;
				if(res == 1) b_mn = x;
			}	
			//printf("a_mn = %d, b_mn = %d\n", a_mn, b_mn);
 
			if(query(a_mn, b_mn) == -1) {
				a.erase(a_mn), a.insert(i);
			}
			else {
				b.erase(b_mn), b.insert(i);
			}
		}
		puts("!");
		fflush(stdout);
	}
	return 0;
}
