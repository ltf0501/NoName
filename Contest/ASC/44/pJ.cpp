#include <bits/stdc++.h>
using namespace std;
const int kN = 5e5 + 10;
int p[kN], sz[kN];
int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}
void Union(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y], p[y] = x;
}
int a[kN];
int c[kN];
int fail[kN], match[kN];
int ans[kN];
bool check(int n) {
	for(int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
	int cnt = 0;
	int len = 0;
	for(int i = n; i >= 1; i--) {
		if(a[i] <= len || a[i] == i) {
			len--;
			continue;
		}
		cnt += a[i];
		if(cnt > 2 * n) return 0;
		for(int j = 1; j <= a[i]; j++) Union(j, i - a[i] + j);
		len = a[i] - 1;
	}
	fail[0] = -1;
	for(int i = 1; i <= n; i++) fail[i] = match[i] = ans[i] = 0;
	for(int i = 1; i <= n; i++) c[i] = find(i);	
	match[1] = ans[1] = 1;
	for(int i = 2, j = 0; i <= n; i++) {
		while(j != -1 && c[j + 1] != c[i]) j = fail[j];
		fail[i] = ++j;
		if(match[ans[fail[i]]] + ans[fail[i]] >= i) 
			ans[i] = ans[fail[i]], match[ans[i]] = i;
		else ans[i] = match[i] = i;
	}
	for(int i = 1; i <= n; i++) 
		if(ans[i] != a[i]) return 0;
	return 1;
}
int main() {
#ifdef ONLINE_JUDGE
	freopen("judges.in", "r", stdin);
	freopen("judges.out", "w", stdout);
#endif
	int n;
	while(~scanf("%d", &n) && n) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		if(check(n)) {
			puts("Yes");
			for(int i = 1; i <= n; i++) printf("%d ", c[i]); puts("");
		}
		else puts("No");
	}

	return 0;
}
