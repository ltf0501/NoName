#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(1E3 + 10), kInf = int(1E8 + 10);
int lf[kN], p[kN], a[kN], t = 1;
vector<pair<int, int>> ans;
void dfs(int pos, int now) {
	if (now == 1) {
		lf[pos] = 1;
		a[pos] = 1;
	}
	else if (now & 1) {
		int l = ++t, ll, lr, nxt;
		p[l] = pos;
		ll = ++t;
		lr = ++t;
		p[lr] = p[ll] = l;
		a[l] = 2;
		a[lr] = a[ll] = 1;
		dfs(nxt = ++t, now >> 1);
		lf[pos] = 2 + lf[nxt];
		a[pos] = lf[pos];
		p[nxt] = pos;
	}
	else {
		int l = ++t, ll, lr, nxt;
		p[l] = pos;
		ll = ++t;
		lr = ++t;
		p[lr] = p[ll] = l;
		a[l] = 2;
		a[lr] = a[ll] = 1;
		dfs(nxt = ++t, now >> 1);
		lf[pos] = 2 + lf[nxt];
		a[pos] = lf[pos] + 1;
		p[nxt] = pos;
	}
	return ;
}
 
int main() {
	int n;
	scanf("%d", &n);
	if(n == 1) {
		printf("2\n1\n2 1\n");
		return 0;
	}
	dfs(1, n);
	
	printf("%d\n", t);
	if (n > 1) printf("%d", p[2]);
	for (int i = 3; i <= t; i++) printf(" %d", p[i]);
	printf("\n%d", a[1]);
	for (int i = 2; i <= t; i++) printf(" %d", a[i]);
	printf("\n");
}
