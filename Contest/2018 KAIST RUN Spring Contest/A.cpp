#include <bits/stdc++.h>
using namespace std;
const int kN = 22;

int n, m, k;
vector<int> v[kN];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int x; scanf("%d", &x);
			if(x) v[j].push_back(x);
		}
	}

	vector<tuple<int, int, int, int>> ans;

	for(int i = 1; i <= m; i++) {
		if(int(v[i].size()) & 1) {
			int x = v[i].back(), y = (x == 1 ? 2 : 1);
			ans.emplace_back(1, i, y, x);
			ans.emplace_back(1, i, y, y);
			ans.emplace_back(1, i, y, y);
			v[i].pop_back();
		}
		reverse(v[i].begin(), v[i].end());
	}

	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < int(v[i].size()); j += 2) {
			ans.emplace_back(1, i, v[i][j + 1], v[i][j]);
		}
	}

	printf("%d\n", int(ans.size()));
	for(auto p : ans) printf("%d %d %d %d\n", get<0>(p), get<1>(p), get<2>(p), get<3>(p));
} 
