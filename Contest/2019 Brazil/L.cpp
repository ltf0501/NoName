#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int64_t n; cin >> n;
	int64_t ans = 1;
	while (n > 1) {
		int64_t pw = 1LL << __lg(n);
		auto rem = n - pw;
		ans *= 2;
		n = rem;
	}
	ans *= n == 1 ? 2 : 1;
	cout << ans << '\n';
} 
