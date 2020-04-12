#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e3 + 10;

vector<int> w[kN];
int n;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < 1LL * n * (n - 1) / 2; i++) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		w[x].push_back(d), w[y].push_back(d);
	}

	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		sort(w[i].begin(), w[i].end(), greater<int>());
		//for(int x : w[i]) printf("%d ", x); puts("");
		for(int j = 0; j < int(w[i].size()); j += 2)
			ans += w[i][j];
	}
	printf("%lld\n", ans);
	return 0;
} 
