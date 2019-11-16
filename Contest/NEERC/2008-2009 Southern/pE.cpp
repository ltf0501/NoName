#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const char TO_CHR[] = { 'L', 'R', 'U', 'D' };

int n;
string str;
tuple<int, int, bool, int, bool> dp[1001][4][2][4][2];
int TO_POS[26];

tuple<int, int, bool, int, bool> dfs(int nn, int lPos, bool lUse, int rPos, bool rUse);

tuple<int, int, bool, int, bool> update(int nn, int lPos, bool lUse, int rPos, bool rUse, int d) {
	return { get<0>(dfs(nn, lPos, lUse, rPos, rUse)) + d, lPos, lUse, rPos, rUse };
}

tuple<int, int, bool, int, bool> dfs(int nn, int lPos, bool lUse, int rPos, bool rUse) {
	if (lPos == 1 && rPos == 0) return { INF, 0, false, 0, false };
	if (nn == n) return { 0, 0, false, 0, false };
	auto &ans = dp[nn][lPos][lUse][rPos][rUse];
	if (get<0>(ans) != INF) return ans;
	if (str[nn] == 'N') {
		ans = min(ans, update(nn + 1, lPos, false, rPos, false, 0));
	}
	if (TO_POS[str[nn] - 'A'] == lPos) {
		ans = min(ans, update(nn + 1, lPos, true, rPos, false, 1));
	}
	if (TO_POS[str[nn] - 'A'] == rPos) {
		ans = min(ans, update(nn + 1, lPos, false, rPos, true, 1));
	}
	for (int i = 0; i < 4; i++) {
		if ((i == TO_POS[str[nn] - 'A'] || str[nn] == 'N') && i != rPos) {
			if (!lUse) {
				ans = min(ans, update(nn + 1, i, true, rPos, false, 3));
			} else {
				ans = min(ans, update(nn + 1, i, true, rPos, false, 9));
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if ((i == TO_POS[str[nn] - 'A'] || str[nn] == 'N') && i != lPos) {
			if (!rUse) {
				ans = min(ans, update(nn + 1, lPos, false, i, true, 3));
			} else {
				ans = min(ans, update(nn + 1, lPos, false, i, true, 9));
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) continue;
			if (str[nn] == 'N' || i == TO_POS[str[nn] - 'A'] || j == TO_POS[str[nn] - 'A']) {
				ans = min(ans, update(nn + 1, i, true, j, true, 10));
			}
		}
	}
	return ans;
}

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	TO_POS['L' - 'A'] = 0;
	TO_POS['R' - 'A'] = 1;
	TO_POS['U' - 'A'] = 2;
	TO_POS['D' - 'A'] = 3;
	TO_POS['N' - 'A'] = 4;
	cin >> n >> str;
	fill(&dp[0][0][0][0][0], &dp[n][3][1][3][1], make_tuple(INF, 0, false, 0, false));
	cout << get<0>(dfs(0, 0, false, 1, false)) << '\n';
	int lPos = 0, lUse = false, rPos = 1, rUse = false;
	for (int i = 0; i < n; i++) {
		int ttmp;
		auto tmp = dp[i][lPos][lUse][rPos][rUse];
		tie(ttmp, lPos, lUse, rPos, rUse) = tmp;
		cout << TO_CHR[lPos] << TO_CHR[rPos] << '\n';
	}
}
