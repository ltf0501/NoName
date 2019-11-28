#include <bits/stdc++.h>
using namespace std;

struct Map {
	int a[6][6];
	vector<tuple<int, int, int>> vech;
};

bool Okay(const Map &cur) {
	return cur.a[2][5] == 1;
}

bool Dfs(Map cur, int left) {
	if (Okay(cur)) {
		return true;
	}
	if (left == 0) return false;
	int idx = 0;
	for (auto t : cur.vech) {
		auto [x, y, dd] = t;
		int d = abs(dd);
		if (dd > 0) {
			if (x + d < 6 && cur.a[x + d][y] == 0) {
				Map nxt = cur;
				swap(nxt.a[x + d][y], nxt.a[x][y]);
				++get<0>(nxt.vech[idx]);
				if (Dfs(nxt, left - 1)) return true;
			}
			if (x > 0 && cur.a[x - 1][y] == 0) {
				Map nxt = cur;
				swap(nxt.a[x - 1][y], nxt.a[x + d - 1][y]);
				--get<0>(nxt.vech[idx]);
				if (Dfs(nxt, left - 1)) return true;
			}
		} else {
			if (y + d < 6 && cur.a[x][y + d] == 0) {
				Map nxt = cur;
				swap(nxt.a[x][y + d], nxt.a[x][y]);
				++get<1>(nxt.vech[idx]);
				if (Dfs(nxt, left - 1)) return true;
			}
			if (y > 0 && cur.a[x][y - 1] == 0) {
				Map nxt = cur;
				swap(nxt.a[x][y - 1], nxt.a[x][y + d - 1]);
				--get<1>(nxt.vech[idx]);
				if (Dfs(nxt, left - 1)) return true;
			}
		}
		++idx;
	}
	return false;
}

int main() {
	cin.tie(0), ios_base::sync_with_stdio(0);
	Map init;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) cin >> init.a[i][j];
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i + 2 < 6 && init.a[i][j] && init.a[i][j] == init.a[i + 1][j] && init.a[i][j] == init.a[i + 2][j]) {
				init.vech.emplace_back(i, j, 3);	
			} else if (i + 1 < 6 && init.a[i][j] && (!i || init.a[i - 1][j] != init.a[i][j]) && init.a[i][j] == init.a[i + 1][j]) {
				init.vech.emplace_back(i, j, 2);	
			}
			if (j + 2 < 6 && init.a[i][j] && init.a[i][j] == init.a[i][j + 1] && init.a[i][j] == init.a[i][j + 2]) {
				init.vech.emplace_back(i, j, -3);	
			} else if (j + 1 < 6 && init.a[i][j] && (!j || init.a[i][j - 1] != init.a[i][j]) && init.a[i][j] == init.a[i][j + 1]) {
				init.vech.emplace_back(i, j, -2);	
			}
		}
	}
	for (int i = 0; i <= 8; i++) {
		if (Dfs(init, i)) {
			cout << i + 2 << '\n';
			return 0;
		}
	}
	cout << "-1\n";
}
