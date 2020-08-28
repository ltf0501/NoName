#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define F first
#define S second
const int kN = 205;
const int kMod = 78294349;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		a = 1LL * a * a % kMod, n >>= 1;
	}
	return res;
}
int n, m;
char c[kN][kN];
pii nxt[kN][kN], tmp_nxt[kN][kN];
int col[kN], row[kN];
bool vis[kN][kN];
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%d%d", &n, &m);
		memset(col, 0, sizeof(col));
		memset(row, 0, sizeof(row));
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i < n; i++) 
			for(int j = 0; j < m; j++) nxt[i][j] = tmp_nxt[i][j] = {-1, -1};
		for(int i = 0; i < n; i++) scanf("%s", c[i]);
		for(int i = 0; i < n / 2; i++) swap(c[i], c[n - 1 - i]);
		//for(int i = 0; i < n; i++) printf("%s\n", c[i]);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(c[i][j] == '#') row[i]++, col[j]++;
			}
		}

		//printf("row: ");
		//for(int i = 0; i < n; i++) printf("%d ", row[i]); puts("");
		//printf("col: ");
		//for(int i = 0; i < m; i++) printf("%d ", col[i]); puts("");

		for(int j = m - 1; j >= 0; j--) {
			int num = 0, cur = j + 1;
			for(int i = 0; i < n; i++) {
				if(c[i][j] == '.') break;
				while(cur < m && col[cur] > col[j] - 1 - i) num++, cur++;
				//printf("i = %d, j = %d, num = %d\n", i, j, num);
				tmp_nxt[i][j] = {col[j] - 1 - i, num};
				//tmp_nxt[i][j].F = n - 1 - tmp_nxt[i][j].F;
				//tmp_nxt[i][j].S = m - 1 - tmp_nxt[i][j].S;
			}
		}

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) if(c[i][j] == '#') {
				auto p = tmp_nxt[i][j];
				nxt[i][j] = tmp_nxt[p.F][p.S];
			}
		}

		//for(int i = 0; i < n; i++) {
		//	for(int j = 0; j < m; j++) {
		//		printf("(%d, %d) ", nxt[i][j].F, nxt[i][j].S); puts("");
		//	}
		//}

		vector<int> v;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) if(c[i][j] == '#') {
				if(vis[i][j]) continue;
				int cnt = 0;
				int curx = i, cury = j;
				do {
					cnt++;
					vis[curx][cury] = 1;
					auto p = nxt[curx][cury];
					curx = p.F, cury = p.S;
				} while(!vis[curx][cury]);
				v.push_back(cnt);
			} 
		}

		//printf("v: ");
		//for(int x : v) printf("%d ", x); puts("");
		map<int, int> mp;
		for(int x : v) {
			int now = x;
			for(int p = 2; p * p <= x; p++) if(now % p == 0) {
				int cnt = 0;
				while(now % p == 0) {
					now /= p, cnt++;
				}
				mp[p] = max(mp[p], cnt);
			}
			if(now > 1) mp[now] = max(mp[now], 1);
		}

		int ans = 1;
		//for(auto it : mp) printf("p = %d, cnt = %d\n", it.F, it.S);
		for(auto it : mp) ans = 1LL * ans * fpow(it.F, it.S) % kMod;
		printf("Case %d: %d\n", ++cas, ans);
	}
	return 0;
} 
