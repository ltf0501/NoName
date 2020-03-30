#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
const int kC = 1e6 + 10;

int n;
int a[kN], sum[kN];
int ans[kC];
set<int> s;

int solve(int x) {
	int r = *s.lower_bound(x);
	int l = *prev(s.lower_bound(x));
	if(ans[l] == ans[r]) return ans[l];
	s.insert(x);
	int cnt = 0, now = 0;
	while(now < n) {
		cnt++;
		int k = upper_bound(sum + 1, sum + n + 1, x + sum[now]) - sum - 1;
		now = k;
	}
	return cnt;
}
int main() {
	scanf("%d", &n);
	int mx = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = a[i] + sum[i - 1], mx = max(mx, a[i]);

	int q; scanf("%d", &q);
	ans[0] = n;
	s.insert(0); s.insert(sum[n] + 1);
	while(q--) {
		int x; scanf("%d", &x);
		if(x < mx) {
			puts("Impossible");
			continue;
		}
		if(ans[x]) printf("%d\n", ans[x]);
		else printf("%d\n", ans[x] = solve(x));
	}
	return 0;
} 
