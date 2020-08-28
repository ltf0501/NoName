#include <bits/stdc++.h>
using namespace std;
const int kN = 505;

char s[kN][kN], ans[kN][kN];
int main() {
	freopen("japanese.in", "r", stdin);
	freopen("japanese.out", "w", stdout);
	
	int n, m; scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", s[i]);

	vector<vector<int>> left, up;
	for(int i = 0; i < n; i++) {
		vector<int> tmp;
		int cnt = 0;
		for(int j = 0; j < m; j++) {
			if(s[i][j] == '.') {
				if(cnt) tmp.push_back(cnt);
				cnt = 0;
			}
			else cnt++;
		}
		if(cnt) tmp.push_back(cnt);
		left.push_back(tmp);
	}
	for(int i = 0; i < m; i++) {
		vector<int> tmp;
		int cnt = 0;
		for(int j = 0; j < n; j++) {
			if(s[j][i] == '.') {
				if(cnt) tmp.push_back(cnt);
				cnt = 0;
			}
			else cnt++;
		}
		if(cnt) tmp.push_back(cnt);
		up.push_back(tmp);
	}

	//for(int i = 0; i < n; i++) {
	//	for(int x : left[i]) printf("%d ", x); puts("");
	//}
	//puts("");
	//for(int i = 0; i < m; i++) {
	//	for(int x : up[i]) printf("%d ", x); puts("");
	//}
	//puts("");

	int N = n, M = m;
  int mxl = 0, mxu = 0;
  for(auto v : left) mxl = max(mxl, int(v.size()));
  for(auto v : up) mxu = max(mxu, int(v.size()));
  N += mxu, M += mxl;

  for(int i = 1; i <= mxu; i++)
		for(int j = 1; j <= mxl; j++) ans[i][j] = '*';
  for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) ans[i + mxu][j + mxl] = '.';

  for(int i = 0; i < n; ++i) {
    int now = mxl;
    for(int j = (int)left[i].size() - 1; j >= 0; j--, now--) ans[i + mxu + 1][now] = (char)(left[i][j] + '0');
    while(now >= 1) ans[i + mxu + 1][now] = '_', now--;
  }
  for(int j = 0; j < m; ++j) {
    int now = mxu;
    for(int i = (int)up[j].size() - 1; i >= 0; i--, now--) ans[now][j + mxl + 1] = (char)(up[j][i] + '0');
    while(now >= 1) ans[now][j + mxl + 1] = '_', now--;
  }

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) printf("%c", ans[i][j]); puts("");
	}
	return 0;
} 
