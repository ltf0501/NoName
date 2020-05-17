#include <bits/stdc++.h>
using namespace std;

char field[3005][3005];
int g[26][6005][26];
bool vis[26][6005][1 << 3], same[26][6005][26], same2[3005][3005], same_pre[3005][3005];

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> field[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i + 1 < n) ++g[field[i][j] - 'a'][i + j][field[i + 1][j] - 'a'];
			if (j + 1 < m) ++g[field[i][j] - 'a'][i + j][field[i][j + 1] - 'a'];
			if (i + 1 < n && j + 1 < m && field[i + 1][j] == field[i][j + 1]) {
				same[field[i][j] - 'a'][i + j][field[i + 1][j] - 'a'] = true;
				same2[i][j] = same_pre[i + 1][j + 1] = true;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			same_pre[i + 1][j + 1] |= same_pre[i][j + 1] | same_pre[i + 1][j];
		}
	}
	bool ok = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ok |= same2[i][j] && same_pre[i][j];
			if (i - 1 >= 0) ok |= same2[i][j] && same2[i - 1][j];
			if (j - 1 >= 0) ok |= same2[i][j] && same2[i][j - 1];
		}
	}
#if 0
	queue<tuple<int, int, int>> q;
	auto Emplace = [&](int ch, int d, int mask) {
		//cerr << ch << ':' << d << ':' << mask << '\n';
		if (vis[ch][d][mask]) return;
		vis[ch][d][mask] = true;
		q.emplace(ch, d, mask);
	};
	Emplace(field[0][0] - 'a', 0, (1 << 3) - 1);
	while (q.size()) {
		auto t = q.front();
		int ch, d, mask;
		std::tie(ch, d, mask) = t;
		q.pop();
		if (d == (n - 1) + (m - 1)) {
			if (mask == 0) {
				ok = true;
				break;
			} else {
				continue;
			}
		}
		for (int i = 0; i < 26; i++) {
			if (same[ch][d][i]) {
				if (mask == (1 << 3) - 1) {
					Emplace(i, d + 1, 0b100);
					Emplace(i, d + 1, 0b010);
					Emplace(i, d + 1, 0b001);
				} else {
					Emplace(i, d + 1, 0);
				}
			}
			if (g[ch][d][i] >= 1) {
				Emplace(i, d + 1, mask);
			}
		}
	}
#endif
	cout << (ok ? "YES\n" : "NO\n");
}

