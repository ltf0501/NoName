#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1010;
using WInt = int32_t;
constexpr WInt kInf = 0x3f3f3f3f;

WInt g[kN][kN];
int n, m;
WInt slack[kN], lx[kN], ly[kN];
int mx[kN], my[kN], vx[kN], vy[kN], timer;
bool vis[kN];

bool Dfs(int x) {
	vx[x] = timer;
	for (int y = 1; y <= m; y++) {
		if (vy[y] == timer) continue;
		auto t = lx[x] + ly[y] - g[x][y];
		if (!t) {
			vy[y] = timer;
			if (!my[y] || Dfs(my[y])) {
				mx[x] = y;
				my[y] = x;
				return true;
			}
		} else {
			slack[y] = min(slack[y], t);
		}
	}
	return false;
}

void Reweight() {
	auto t = kInf;
	for (int y = 1; y <= m; y++) {
		if (vy[y] != timer) t = min(t, slack[y]);
	}
	for (int x = 1; x <= n; x++) {
		if (vx[x] == timer) lx[x] -= t;
	}
	for (int y = 1; y <= m; y++) {
		if (vy[y] == timer) ly[y] += t;
	}
}

void Km() {
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	memset(mx, 0, sizeof(mx));
	memset(my, 0, sizeof(my));
	for (int x = 1; x <= n; x++) {
		lx[x] = -kInf;
		for (int y = 1; y <= m; y++) {
			lx[x] = max(lx[x], g[x][y]);
		}
	}
	for (int x = 1; x <= n; x++) {
		for (;;) {
			++timer;
			memset(slack, kInf, sizeof(slack));
			if (Dfs(x)) break;
			else Reweight();
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%d", &n);
		m = n;
		for(int i = 1; i <= n; i++) {
			g[i][i] = kInf;
			for(int j = i + 1; j <= n; j++) {
				scanf("%d", &g[i][j]);
				g[j][i] = g[i][j];
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) g[i][j] = -g[i][j];
		}

		Km();
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += g[i][mx[i]];
		printf("Case %d: %d\n", ++cas, -ans);
	}
	return 0;
} 
