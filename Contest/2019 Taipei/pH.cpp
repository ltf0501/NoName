#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int64_t nn = 1LL * n * n;
		int64_t ans = 0;
		for (int i = 1; i <= n; i++) {
			if (nn % i == 0) {
				// x - n == i, y - n == nn / i
				// x == i + n, y == nn / i + n
				int64_t x = i + n, y = nn / i + n;
				if (x > 0 && y > 0) {
					ans = max(ans, x ^ y);
				}
			}
		}
		cout << ans << '\n';
	}
}
