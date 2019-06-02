#include <bits/stdc++.h>
using namespace std;

int n, m;
string str[50];

int cnt, minCnt = 0x3f3f3f3f;
vector<int> clazz[13], ansClazz[13], related[13];
int conv[13];
bool used[26 * 26];

void dfs(int nn, int cnt) {
	// if (cnt >= minCnt) return;
	if (nn == n) {
		if (cnt < minCnt) {
			minCnt = cnt;
			for (int i = 0; i < cnt; i++) ansClazz[i] = clazz[i];
		}
	} else {
		for (int i = 0; i < cnt; i++) {
			bool fail = false;
			int j;
			for (j = 0; j < int(related[nn].size()); j++) {
				int k = related[nn][j];
				int x = str[k][0] - 'a', y = str[k][1] - 'a';
				if (x == nn) x = 13 + i;
				if (x < nn) x = 13 + conv[x];
				if (y == nn) y = 13 + i;
				if (y < nn) y = 13 + conv[y];
				if (used[x * 26 + y]) {
					fail = true;
					break;
				}
				used[x * 26 + y] = true;
			}
			if (!fail) {
				clazz[i].push_back(nn);
				conv[nn] = i;
				dfs(nn + 1, cnt);
				assert(clazz[i].back() == nn);
				clazz[i].pop_back();
			}
			for (j-- ; j >= 0; j--) {
				int k = related[nn][j];
				int x = str[k][0] - 'a', y = str[k][1] - 'a';
				if (x == nn) x = 13 + i;
				if (x < nn) x = 13 + conv[x];
				if (y == nn) y = 13 + i;
				if (y < nn) y = 13 + conv[y];
				used[x * 26 + y] = false;
			}
		}
		{
			bool fail = false;
			int j;
			for (j = 0; j < int(related[nn].size()); j++) {
				int k = related[nn][j];
				int x = str[k][0] - 'a', y = str[k][1] - 'a';
				if (x == nn) x = 13 + cnt;
				if (x < nn) x = 13 + conv[x];
				if (y == nn) y = 13 + cnt;
				if (y < nn) y = 13 + conv[y];
				if (used[x * 26 + y]) {
					fail = true;
					break;
				}
				used[x * 26 + y] = true;
			}
			if (!fail) {
				clazz[cnt].push_back(nn);
				conv[nn] = cnt;
				dfs(nn + 1, cnt + 1);
				assert(clazz[cnt].back() == nn);
				clazz[cnt].pop_back();
			}
			for (j-- ; j >= 0; j--) {
				int k = related[nn][j];
				int x = str[k][0] - 'a', y = str[k][1] - 'a';
				if (x == nn) x = 13 + cnt;
				if (x < nn) x = 13 + conv[x];
				if (y == nn) y = 13 + cnt;
				if (y < nn) y = 13 + conv[y];
				used[x * 26 + y] = false;
			}
		}
	}
}

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> str[i];
		related[str[i][0] - 'a'].push_back(i);
		related[str[i][1] - 'a'].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		sort(related[i].begin(), related[i].end());
		related[i].resize(unique(related[i].begin(), related[i].end()) - related[i].begin());
	}
	dfs(0, 0);
	assert(cnt == 0);
	cout << minCnt << endl;
	for (int i = 0; i < minCnt; i++) {
		for (int x: ansClazz[i]) cout << char('a' + x);
		cout << '\n';
	}
}
