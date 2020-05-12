#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const int kMod = 1e9 + 7;

int a[kN], b[kN];
int len_a[kN], len_b[kN];
bool vis[kN];
bool flag[kN];
int cnt[kN];
int main() {
	int n, m;
	int cas = 0;
	while(~scanf("%d%d", &n, &m)) {
		for(int i = 0; i < n; i++) scanf("%d", a + i);
		for(int i = 0; i < m; i++) scanf("%d", b + i);
		for(int i = 1; i <= max(m, n); i++) cnt[i] = 0;
		for(int i = 0; i < n; i++) flag[i] = 0;

		for(int i = 0; i < n; i++) vis[i] = 0;	
		for(int i = 0; i < n; i++) if(!vis[i]) {
			vector<int> v;
			int now = i;
			flag[i] = 1;
			while(true) {
				vis[now] = 1;
				v.push_back(now);
				now = a[now];
				if(now == i) break;
			}
			int sz = v.size();
			for(int x : v) len_a[x] = sz;
		}

		for(int i = 0; i < m; i++) vis[i] = 0;	
		for(int i = 0; i < m; i++) if(!vis[i]) {
			vector<int> v;
			int now = i;
			while(true) {
				vis[now] = 1;
				v.push_back(now);
				now = b[now];
				if(now == i) break;
			}
			int sz = v.size();
			cnt[sz] += sz;
		}

		for(int i = max(m, n); i >= 1; i--) {
			for(int j = 2 * i; j <= max(m, n); j += i) {
				cnt[j] += cnt[i];
			}
		}

		int ans = 1;
		for(int i = 0; i < n; i++) if(flag[i]) {
			int x = len_a[i];	
			ans = 1LL * ans * cnt[x] % kMod;
		}
		printf("Case #%d: %d\n", ++cas, ans);
	}
	return 0;
} 
