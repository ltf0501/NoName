nclude <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
 
using namespace std;
constexpr int kN = int(1E2 + 10);
 
#define F first
#define S second
#define PB push_back
 
int n, m, a[kN][kN];
 
int ask(int p, vector<int> &ans) {
	ans.clear();
	long long int l = 0, r = 0;
	int now = 0;
	vector<pair<pair<int, int>, int>> v;
	for (int i = 1 ; i <= m; i++) {
		l += a[i][p];
		r += a[i][n];
		v.PB({{a[i][p], a[i][n]}, i});
	}
	auto cmp = [&](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
		return a.F.F - a.F.S < b.F.F - b.F.S;
	};
	sort(v.begin(), v.end(), cmp);
	while (r > l) {
		ans.PB(v[now].S);
		l -= v[now].F.F;
		r -= v[now].F.S;
		now++;
	}
	return int(ans.size());
}
 
int main() {
	vector<int> tmp, o;
	int ans = kN, x;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) for (int j = 1; j <= n ; j++) scanf("%d", &a[i][j]);
	
	for (int i = 1;i < n; i++) {
		x = ask(i, tmp);
		if (x < ans) {
			ans = x;
			o = tmp;
		}
	}
 
	printf("%d\n", ans);
	if (ans > 0) printf("%d", o[0]);
	for (int i = 1; i < ans; i++) printf(" %d", o[i]);
	printf("\n");
}
