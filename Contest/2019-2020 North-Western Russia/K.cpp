#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(1E3 + 10);

string s[kN];
char c[kN][kN];
int xpos[kN], ypos[kN], map_prefix[kN][kN];
vector<pair<int, int>> letters;


void dfs(int x1, int y1, int x2, int y2, vector<int> v) {
	if (int(v.size()) == 1) {
		for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) 
			if (c[i][j] == '.') c[i][j] = v[0] + 'a';
	}
	else {
		vector<int> l, r;
		if (xpos[v[0]] == xpos[v[1]]) {
			if (ypos[v[0]] > ypos[v[1]]) swap(v[0], v[1]);
			for (int i : v) if (ypos[i] <= ypos[v[0]]) l.push_back(i);
			else r.push_back(i);
			dfs(x1, y1, x2, ypos[v[0]], l);
			dfs(x1, ypos[v[0]] + 1, x2, y2, r);
		}
		else {
			if (xpos[v[0]] > xpos[v[1]]) swap(v[0], v[1]);
			for (int i : v) if (xpos[i] <= xpos[v[0]]) l.push_back(i);
			else r.push_back(i);
			dfs(x1, y1, xpos[v[0]], y2, l);
			dfs(xpos[v[0]] + 1, y1, x2, y2, r);
		}
	}
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> s[i];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) c[i][j] = s[i][j - 1];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (c[i][j] !='.') {
		xpos[c[i][j] - 'A'] = i;
		ypos[c[i][j] - 'A'] = j;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			map_prefix[i + 1][j + 1] =
				map_prefix[i - 1 + 1][j + 1] + map_prefix[i + 1][j - 1 + 1] - map_prefix[i - 1 + 1][j - 1 + 1] + (c[i][j] != '.');
			if (c[i][j] != '.') letters.emplace_back(i, j);
		}
	}
	auto query_in = [&](int l, int r, int u, int d) {
		return map_prefix[letters[d].first - 1 + 1][letters[r].second - 1 + 1]
			- map_prefix[letters[u].first + 1][letters[r].second - 1 + 1]
			- map_prefix[letters[d].first - 1 + 1][letters[l].second + 1]
			+ map_prefix[letters[u].first + 1][letters[l].second + 1];
	};
	letters.emplace_back(0, 0);
	letters.emplace_back(0, m + 1);
	letters.emplace_back(n + 1, m + 1);
	letters.emplace_back(n + 1, 0);
	int ls = int(letters.size());
	auto ans = make_tuple(0LL, -1, -1, -1, -1);
	for (int l = 0; l < ls; l++) {
		for (int r = 0; r < ls; r++) {
			for (int u = 0; u < ls; u++) {
				for (int d = 0; d < ls; d++) {
					if (letters[d].first - letters[u].first - 1 >= 0
							&& letters[r].second - letters[l].second - 1 >= 0
							&& letters[u].first + 1 <= xpos[0] && xpos[0] <= letters[d].first - 1
							&& letters[l].second + 1 <= ypos[0] && ypos[0] <= letters[r].second - 1
							&& query_in(l, r, u, d) == 1) {
						ans = max(ans, {(letters[d].first - letters[u].first - 1) * (letters[r].second - letters[l].second - 1), l, r, u, d});
					}
				}
			}
		}
	}
	int jhffgklwer, l, r, u, d;
	vector<int> v;
	std::tie(jhffgklwer, l, r, u, d) = ans;
	int x1 = letters[u].first + 1, x2 = letters[d].first - 1;
	int y1 = letters[l].second + 1, y2 = letters[r].second - 1;

	if (x1 > 1) {
		v.clear();
		for (int i = 1; i < x1; i++) for (int j = 1; j <= m; j++) if (c[i][j] != '.') v.push_back(c[i][j] - 'A');
		dfs(1, 1, x1 - 1, m, v);
	}
	if (x2 < n) {
		v.clear();
		for (int i = x2 + 1; i <= n; i++) for (int j = 1; j <= m; j++) if (c[i][j] != '.') v.push_back(c[i][j] - 'A');
		dfs(x2 + 1, 1, n, m, v);
	}
	if (y1 > 1) {
		v.clear();
		for (int i = x1; i <= x2; i++) for (int j = 1; j < y1; j++) if (c[i][j] != '.') v.push_back(c[i][j] - 'A');
		dfs(x1, 1, x2, y1 - 1, v);
	}
	if (y2 < m) {
		v.clear();
		for (int i = x1; i <= x2; i++) for (int j = y2 + 1; j <= m; j++) if (c[i][j] != '.') v.push_back(c[i][j] - 'A');
		dfs(x1, y2 + 1, x2, m, v);
	}
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			if (c[i][j] == '.') c[i][j] = 'a';
		}
	}
	for (int i = 1; i <= n; i++, cout << endl) for (int j = 1; j <= m; j++) cout << c[i][j];
} 
