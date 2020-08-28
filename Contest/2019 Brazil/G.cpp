#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1010;
using WInt = double;
constexpr WInt kInf = 1e9, kEps = 1e-6;
WInt g[kN][kN];
int n, m;
WInt slack[kN], lx[kN], ly[kN];
int mx[kN], my[kN], vx[kN], vy[kN], timer;
bool Dfs(int x) {
	vx[x] = timer;
	for (int y = 1; y <= m; y++) {
		if (vy[y] == timer) continue;
		auto t = lx[x] + ly[y] - g[x][y];
		if (abs(t) < kEps) {
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
		for (int y = 1; y <= m; y++) lx[x] = max(lx[x], g[x][y]);
	}
	for (int x = 1; x <= n; x++) {
		for (;;) {
			++timer;
			fill_n(slack, n + 1, kInf);
			if (Dfs(x))
				break;
			else
				Reweight();
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> n;
	m = n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
			g[i][j] = log(g[i][j]);
		}
	}
	Km();
	for (int j = 1; j <= m; j++) cout << my[j] << ' ';
	cout << '\n';
} 
