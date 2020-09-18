#include <bits/stdc++.h>
using namespace std;

constexpr pair<int, int> kDirs[4] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
constexpr int kN = 101, kInf = 0x3f3f3f3f;

vector<pair<int, int>> g0[kN][kN], g1[kN][kN];
int dist0[kN][kN], dist1[kN][kN], order[kN][kN], timer, n, m;
bool possible;
tuple<int, int, int, int, char> ans;

int chr2dir(char c) {
	constexpr char str[] = "NEWS";
	return strchr(str, c) - str;
}

void Dfs1(int i, int j) {
	order[i][j] = ++timer;
	for (auto [nx, ny] : g1[i][j]) Dfs1(nx, ny);
	// Tie breaker: ENSW
	for (int k = 0; k < n; k++) {
		if (k == i) continue;
		if (order[i][j] <= order[k][j] && order[k][j] <= timer) continue;
		possible |= dist0[i][j] + 1 + dist1[k][j] < kInf;
		ans = min(ans, make_tuple(dist0[i][j] + 1 + dist1[k][j], i, j, abs(i - k), k < i ? 'N' : 'S'));
	}
	for (int k = 0; k < m; k++) {
		if (k == j) continue;
		if (order[i][j] <= order[i][k] && order[i][k] <= timer) continue;
		possible |= dist0[i][j] + 1 + dist1[i][k] < kInf;
		ans = min(ans, make_tuple(dist0[i][j] + 1 + dist1[i][k], i, j, abs(j - k), k < j ? 'W' : 'E'));
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int cases = 0;
	while (cin >> n >> m && n) {
		timer = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				g0[i][j].clear();
				g1[i][j].clear();
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i == n - 1 && j == m - 1) break;
				int steps;
				char ch_d;
				cin >> steps >> ch_d;
				auto d = kDirs[chr2dir(ch_d)];
				int nx = i + d.first * steps, ny = j + d.second * steps;
				if (0 <= nx && nx < n && 0 <= ny && ny < m) {
					g0[i][j].emplace_back(nx, ny);
					g1[nx][ny].emplace_back(i, j);
				}
			}
		}
		memset(dist0, 0x3f, sizeof(dist0));
		dist0[0][0] = 0;
		queue<pair<int, int>> q;
		q.emplace(0, 0);
		while (!q.empty()) {
			auto [x, y] = q.front();
			q.pop();
			for (auto [nx, ny] : g0[x][y]) {
				if (dist0[nx][ny] > dist0[x][y] + 1) {
					dist0[nx][ny] = dist0[x][y] + 1;
					q.emplace(nx, ny);
				}
			}
		}
		memset(dist1, 0x3f, sizeof(dist1));
		q.emplace(n - 1, m - 1);
		dist1[n - 1][m - 1] = 0;
		while (!q.empty()) {
			auto [x, y] = q.front();
			q.pop();
			for (auto [nx, ny] : g1[x][y]) {
				if (dist1[nx][ny] > dist1[x][y] + 1) {
					dist1[nx][ny] = dist1[x][y] + 1;
					q.emplace(nx, ny);
				}
			}
		}
		memset(order, 0x3f, sizeof(order));
		possible = false;
		ans = {dist0[n - 1][m - 1], -1, -1, -1, 'X'};
		Dfs1(n - 1, m - 1);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (order[i][j] == kInf) {
					for (int k = 0; k < n; k++) {
						if (k == i) continue;
						possible |= dist0[i][j] + 1 + dist1[k][j] < kInf;
						ans = min(ans, make_tuple(dist0[i][j] + 1 + dist1[k][j], i, j, abs(i - k), k < i ? 'N' : 'S'));
					}
					for (int k = 0; k < m; k++) {
						if (k == j) continue;
						possible |= dist0[i][j] + 1 + dist1[i][k] < kInf;
						ans = min(ans, make_tuple(dist0[i][j] + 1 + dist1[i][k], i, j, abs(j - k), k < j ? 'W' : 'E'));
					}
				}
			}
		}
		cout << "Case " << ++cases << ": ";
		if (n == 1 && m == 1) {
			cout << "none 0";
		} else if (!possible) {
			cout << "impossible";
		} else if (get<4>(ans) == 'X') {
			cout << "none " << get<0>(ans);
		} else {
			cout << get<1>(ans) << ' ' << get<2>(ans) << ' ' << get<3>(ans) << get<4>(ans) << ' ' << get<0>(ans);
		}
		cout << '\n';
	}
} 
