#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int64_t n, k;
	int cases = 0;
	while (cin >> n >> k) {
		int64_t a = 0;
		if (k <= n) {
			a = k;
		} else {
			k -= n + 1;
			a = k % (n - 1) + 1;
			k /= n - 1;
			int64_t b = k % 2 ? n - 1 : n;
			cerr << a << ' ' << b << '\n';
			if (b <= a) a++;
		}
		cout << "Case #" << ++cases << ": " << a << '\n';
	}
} 
