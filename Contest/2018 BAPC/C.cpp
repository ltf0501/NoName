#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	auto Calc = [&](int64_t a, int64_t b, int64_t c) {
		return 2 * (a * b + b * c + c * a);
	};
	int64_t ans = INT64_MAX;
	for (int a = 1; a <= n; a++) {
		if (n % a != 0) continue;
		int bc = n / a;
		for (int b = 1; b * b <= bc; b++) {
			if (bc % b != 0) continue;
			ans = min(ans, Calc(a, b, bc / b));
		}
	}
	cout << ans << '\n';
} 
