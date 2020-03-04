#include <bits/stdc++.h>
using namespace std;
 
char field[1000][1000];
 
int main() {
	int n, m; cin >> n >> m;
	int ans = 0;
	bool fail = false;
	for (int i = 0; i < n; i++) cin >> field[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int mi = n - i - 1, mj = m - j - 1;
			if (mi == i && mj == j) {
				if (field[i][j] != '8') fail = true;
			}
			if (field[i][j] == '7' && field[mi][mj] == '7') {
				++ans;
			} else if (field[i][j] == '8' && field[mi][mj] == '8') {
				ans += 0;
			} else if (field[i][j] == '6' && field[mi][mj] == '6') {
				++ans;
			} else if (field[i][j] == '9' && field[mi][mj] == '9') {
				++ans;
			} else if (field[i][j] == '9' && field[mi][mj] == '6') {
				ans += 0;
			} else if (field[i][j] == '6' && field[mi][mj] == '9') {
				ans += 0;
			} else {
				fail = true;
			}
		}
	}
	if (fail) cout << -1 << '\n';
	else cout << ans / 2 << '\n';
}
