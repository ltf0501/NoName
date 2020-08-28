#include <bits/stdc++.h>
using namespace std;

#define PB push_back
constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);

int dp[kN][3][3][3]; // Q = 0, W = 1, E = 2
string skill[10] = {"QQQ", "QQW", "QQE", "WWW", "QWW", "WWE", "EEE", "QEE", "WEE", "QWE"};
char c[10] = {'Y', 'V', 'G', 'C', 'X', 'Z', 'T', 'F', 'D', 'B'};
int toc[26], tt[26];
vector<tuple<int, int, int>> p[10];

tuple<int, int, int> tu(string s) {
	return {tt[s[0] - 'A'], tt[s[1] - 'A'], tt[s[2] - 'A']};
}

void pre() {
	for (int i = 0; i < 10; i++) toc[c[i] - 'A'] = i;
	tt['Q' - 'A'] = 0, tt['W' - 'A'] = 1, tt['E' - 'A'] = 2;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++) {
			next_permutation(skill[i].begin(), skill[i].end());
			p[i].PB(tu(skill[i]));
		}
		sort(p[i].begin(), p[i].end());
		p[i].resize(unique(p[i].begin(), p[i].end()) - p[i].begin());
	}
	return ;
}

int val(int x, int y, int z, int a, int b, int c) {
	if (x == a && y == b && z == c) return 0;
	else if (y == a && z == b) return 1;
	else if (z == a) return 2;
	else return 3;
}

int main() {
	pre();
	int n, ans = kInf;
	string s;
	cin >> s;
	n = int(s.size());
	for (int i = 0; i < n; i++) for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) dp[i][x][y][z] = kInf;
	for (tuple<int, int, int> i : p[toc[s[0] - 'A']]) dp[0][get<0>(i)][get<1>(i)][get<2>(i)] = 3;

	for (int i = 1; i < n; i++) {
		for (tuple<int, int, int> j : p[toc[s[i] - 'A']]) {
			for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) for (int z = 0; z < 3; z++) {
				dp[i][get<0>(j)][get<1>(j)][get<2>(j)] = min(dp[i][get<0>(j)][get<1>(j)][get<2>(j)], dp[i - 1][x][y][z] + val(x, y, z, get<0>(j), get<1>(j), get<2>(j)));
			}
		}
	}

	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) for (int k = 0; k < 3; k++) ans = min(ans, dp[n - 1][i][j][k]);
	cout << ans + n << '\n';

} 
