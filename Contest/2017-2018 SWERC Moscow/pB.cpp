nclude <bits/stdc++.h>
using namespace std;
 
constexpr int kN = 2019;
 
int table[kN][kN], ans[kN][kN];
 
int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	int xx, yy, n, d; cin >> xx >> yy >> n >> d;
	while (n--) {
		int x1, x2, y1, y2; cin >> x1 >> x2 >> y1 >> y2;
		++x1, ++y1;
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) table[x][y] = -1;
		}
	}
	for (int x = xx; x; x--) {
		for (int y = yy; y; y--) {
			table[x][y] = table[x][y] ? 0 : table[x + 1][y] + 1;
		}
	}
	for (int x = 1; x <= xx; x++) {
		stack<pair<int, int>> stk;
		for (int y = 1; y <= yy + 1; y++) {
			int left = y;
			while (stk.size() && stk.top().second >= table[x][y]) {
				auto p = stk.top(); stk.pop();
				++ans[p.second][y - p.first];
				int hei = stk.size() ? max(table[x][y], stk.top().second) : table[x][y];
				if (hei) --ans[hei][y - p.first];
				left = p.first;
			}
			if (table[x][y]) stk.emplace(left, table[x][y]);
		}
	}
	for (int x = xx; x >= 0; x--) {
		for (int y = yy; y >= 0; y--) ans[x][y] += ans[x][y + 1];
	}
	for (int x = xx; x >= 0; x--) {
		for (int y = yy; y >= 0; y--) {
			ans[x][y] += ans[x + 1][y] + ans[x][y + 1] - ans[x + 1][y + 1];
		}
	}
	while (d--) {
		int qx, qy; cin >> qx >> qy;
		cout << ans[qx][qy] << '\n';
	}
}
