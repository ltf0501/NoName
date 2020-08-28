#include <bits/stdc++.h>
using namespace std;

constexpr int kInf = 0x3f3f3f3f;
constexpr pair<int, int> kDir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
constexpr char kDir2Chr[] = "RFLB";

string ans;
int m, n;
double t0;

tuple<int, int, char, bool> CheckDir(int x, int y, char dir, int i) {
	int nx = x + kDir[i].first, ny = y + kDir[i].second;
	if (nx < 1 || m < nx || ny < 1 || n < ny) return {0, 0, '\0', false};
	constexpr char kDirS[2][5] = {"TFDB", "TRDL"};
	int kind = !!kDir[i].second, dd = kind ? kDir[i].second : kDir[i].first;
	auto *p = strchr(kDirS[kind], dir);
	if (!p) return {nx, ny, dir, dir != 'D'};
	char nd = *(kDirS[kind] + (p - kDirS[kind] + dd + 4) % 4);
	return {nx, ny, nd, nd != 'D'};
}

int Idas(int x, int y, char dir, int max_cost, int c, int d) {
	//cerr << x << ' ' << y << ' ' << dir << ' ' << max_cost << '\n';
	static int loopcnt = 0;
	if ((++loopcnt & ((1 << 10) - 1)) == 0 && (clock() - t0) / CLOCKS_PER_SEC > 0.49) {
		cout << "IMPOSSIBLE\n";
		exit(0);
	}
	if (x == c && y == d) return 0;
	int h = abs(x - c) + abs(y - d);
	if (h > max_cost) return h;
	int mn = kInf;
	for (int idx = 0; idx < 4; idx++) {
		auto [nx, ny, nd, ok] = CheckDir(x, y, dir, idx);
		if (!ok) continue;
		ans.push_back(kDir2Chr[idx]);
		int res = Idas(nx, ny, nd, max_cost - 1, c, d);
		if (res + 1 <= max_cost) return res + 1;
		mn = min(mn, res + 1);
		ans.pop_back();
	}
	return mn;
}

int main() {
	t0 = clock();
	freopen("delivery.in", "r", stdin);
	freopen("delivery.out", "w", stdout);
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int b, c, d; cin >> m >> n >> b >> c >> d;
	char dir; cin >> dir;
	for (int i = 0; i <= 4 * (m + n); ) {
		int res = Idas(1, b, dir, i, c, d);
		if (res <= i) {
			cout << ans << '\n';
			exit(0);
		}
		i = res;
	}
	cout << "IMPOSSIBLE\n";
} 
