#include <bits/stdc++.h>
using namespace std;
 
pair<int64_t, int64_t> ans{1e9, 0};
 
void doo(int64_t x, int64_t y) {
	//cerr << x << ' ' << y << '\n';
	auto b = (y + x - 1);
	auto a = (y - x + 1);
	if ((a & 1) || (b & 1)) return;
	if (a >= b) return;
	if (a <= 0) return;
	a >>= 1, b >>= 1;
	ans = min(ans, {b - a, a});
}
 
int main() {
	cin.tie(0), ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while (t--) {
		int64_t n; cin >> n;
		auto nnn = n;
		ans = {1e9, 0};
		auto n2 = n * 2;
		int64_t poww = 1;
		while (n % 2 == 0) {
			n >>= 1;
			poww <<= 1;
		}
		poww <<= 1;
		for (int64_t x = 3; x * x <= n; x++) {
			if (n % x == 0) {
				doo(x, n2 / x);
				break;
			}
		}
		doo(n,n2 /  n);
		doo(poww, n2 / poww);
		if (ans.first == 1e9) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		cout << nnn << " = ";
		for (int i = ans.second; i <= ans.second + ans.first; i++) {
			if (i != ans.second) cout << " + ";
			cout << i;
		}
		cout << '\n';
	}
}
