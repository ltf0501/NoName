#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	int cases = 0;
	while (t--) {
		int n; cin >> n;
		bool ans = true;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			ans &= x % 3 == 0;
		}
		cout << "Case #" << ++cases << ": " << (ans ? "Yes\n" : "No\n");
	}
} 
