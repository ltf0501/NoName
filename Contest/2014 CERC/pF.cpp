#include <bits/stdc++.h>
using namespace std;
 
constexpr int kN = 1000010, kMod = 1E9 + 9;
constexpr char kNull = 'a' - 1, kQmark = 'z' + 1;
 
int preproc[28][28][28][3][3];
 
int cmp(int x, int y) {
	return x < y ? 0 : x == y ? 1 : 2;
}
 
int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	for (int q_cnt = 0; q_cnt <= 3; q_cnt++) {
		for (int x = 0; x <= kQmark - kNull; x++) {
			for (int y = 0; y <= kQmark - kNull; y++) {
				for (int z = 0; z <= kQmark - kNull; z++) {
					int q_cnt_cur =
						(x == kQmark - kNull) +
						(y == kQmark - kNull) +
						(z == kQmark - kNull);
					if (q_cnt_cur != q_cnt) continue;
					auto &cur = preproc[x][y][z];
					if (q_cnt_cur == 0) {
						int &val = cur[cmp(x, y)][cmp(y, z)];
						val = (val + 1) % kMod;
					} else if (x == kQmark - kNull) {
						for (int xx = 'a' - kNull; xx < kQmark - kNull; xx++) {
							for (int i = 0; i <= 2; i++) {
								for (int j = 0; j <= 2; j++) {
									cur[i][j] = (cur[i][j] + preproc[xx][y][z][i][j]) % kMod;
								}
							}
						}
					} else if (y == kQmark - kNull) {
						for (int yy = 'a' - kNull; yy < kQmark - kNull; yy++) {
							for (int i = 0; i <= 2; i++) {
								for (int j = 0; j <= 2; j++) {
									cur[i][j] = (cur[i][j] + preproc[x][yy][z][i][j]) % kMod;
								}
							}
						}
					} else { // if (z == kQmark - kNull)
						for (int zz = 'a' - kNull; zz < kQmark - kNull; zz++) {
							for (int i = 0; i <= 2; i++) {
								for (int j = 0; j <= 2; j++) {
									cur[i][j] = (cur[i][j] + preproc[x][y][zz][i][j]) % kMod;
								}
							}
						}
					}
				}
			}
		}
	}
	int t; cin >> t;
	while (t--) {
		int64_t dp[2][3][3] = {};
		string str[3];
		for (int i = 0; i < 3; i++) {
			cin >> str[i];
			for (char &c : str[i]) {
				c = c == '?' ? kQmark : c;
				c = char(c - kNull);
			}
		}
		auto sz = max({str[0].size(), str[1].size(), str[2].size()});
		for (int i = 0; i < 3; i++) {
			while (str[i].size() < sz) str[i].push_back(0);
		}
		constexpr int kNxt[][3] = {{0, 0, 0}, {0, 1, 2}};
		dp[0][1][1] = 1;
		for (int i = 0; i < int(sz); i++) {
			memset(dp[~i & 1], 0, sizeof(dp[~i & 1]));
			for (int s0 = 0; s0 < 2; s0++) {
				for (int t0 = 0; t0 <= 2; t0++) {
					for (int s1 = 0; s1 < 2; s1++) {
						for (int t1 = 0; t1 <= 2; t1++) {
							auto &x = dp[~i & 1][kNxt[s0][t0]][kNxt[s1][t1]];
							x = (
									x +
										dp[i & 1][s0][s1] *
										preproc[str[0][i]][str[1][i]][str[2][i]][t0][t1]
								) % kMod;
						}
					}
				}
			}
		}
		cout << dp[sz & 1][0][0] << '\n';
	}
}
