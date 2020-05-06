#include <bits/stdc++.h>
using namespace std;

int kind[1010][1010], h, w;
char field[1010][1010];

enum Kind {
	kTypeUnvis,
	kTypeBorder,
	kTypeBg,
	kTypeLetter,
	kTypeNoise,
	kTypeInside
};

void Dfs(int x, int y, char c, int k, bool diag) {
	if (x < 0 || x >= h || y < 0 || y >= w) return;
	if (kind[x][y] != kTypeUnvis || field[x][y] != c) return;
	kind[x][y] = k;
	if (diag) {
		for (int xx = x - 1; xx <= x + 1; xx++) {
			for (int yy = y - 1; yy <= y + 1; yy++) {
				Dfs(xx, yy, c, k, diag);
			}
		}
	} else {
		Dfs(x + 1, y, c, k, diag);
		Dfs(x, y + 1, c, k, diag);
		Dfs(x - 1, y, c, k, diag);
		Dfs(x, y - 1, c, k, diag);
	}
}

void Dfs1(int x, int y) {
	if (x < 0 || x >= h || y < 0 || y >= w) return;
	if (kind[x][y] != kTypeUnvis) return;
	if (field[x][y] == '.') {
		Dfs(x, y, '.', kTypeBg, false);
		return;
	}
	kind[x][y] = kTypeBorder;
	for (int xx = x - 1; xx <= x + 1; xx++) {
		for (int yy = y - 1; yy <= y + 1; yy++) {
			Dfs1(xx, yy);
		}
	}
	return;
}

int Dfs2(int x, int y) {
	if (x < 0 || x >= h || y < 0 || y >= w) return 0;
	if (kind[x][y] != kTypeUnvis) return 0;
	if (field[x][y] == '.') {
		Dfs(x, y, '.', kTypeInside, false);
		return 1;
	}
	kind[x][y] = kTypeLetter;
	return Dfs2(x + 1, y) +
		Dfs2(x, y + 1) +
		Dfs2(x - 1, y) +
		Dfs2(x, y - 1);
}

bool CheckIsNoise(int x, int y) {
	if (kind[x][y] != kTypeUnvis) return kind[x][y] == kTypeNoise;
	for (int xx = x - 1; xx <= x + 1; xx++) {
		for (int yy = y - 1; yy <= y + 1; yy++) {
			if (xx < 0 || xx >= h || yy < 0 || yy >= w) return false;
			char targ = (xx == x && yy == y) ? '#' : '.';
			if (field[xx][yy] != targ) return false;
		}
	}
	kind[x][y] = kTypeNoise;
	return true;
}

void PrintVis() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cerr << kind[i][j];
		}
		cerr << '\n';
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> w >> h;
	for (int i = 0; i < h; i++) {
		cin >> field[i];
	}
	assert(field[0][0] == '#');
	Dfs1(0, 0);
	[&]() {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (field[i][j] == '.') {
					Dfs(i, j, '.', kTypeBg, false);
					return;
				}
			}
		}
		assert(0);
	}();
	PrintVis();
	int cnt[3] = {};
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (kind[i][j]) continue;
			if (CheckIsNoise(i, j)) continue;
			if (field[i][j] == '#') {
				int k = Dfs2(i, j);
				++cnt[k];
			}
		}
	}
	cout << cnt[1] << ' ' << cnt[2] << ' ' << cnt[0] << '\n';
} 
