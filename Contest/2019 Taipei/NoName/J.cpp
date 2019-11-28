#include <bits/stdc++.h>
using namespace std;

using BS = bitset<512>;

BS bits[16];

int main() {
	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		for (int i = 0; i < m; i++) {
			string str; cin >> str;
			bits[i].reset();
			for (char c : str) {
				bits[i] = bits[i] << 1 | BS(c - '0');
			}
		}
		int ans = INT_MAX;
		for (int i = 0; i < (1 << m); i++) {
			BS tot;
			for (int j = 0; j < m; j++) {
				if (i & (1 << j)) tot |= bits[j];
			}
			if (tot.count() == n) ans = min(ans, __builtin_popcount(i));
		}
		if (ans == INT_MAX) ans = -1;
		cout << ans << '\n';
	}
}
