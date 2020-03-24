#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		if (n <= 5) {
			cout << -1 << '\n';
		} else if (n % 2 == 0) {
			cout << 2 << ' ' << n - 2 << '\n';
		} else {
			cout << 3 << ' ' << n - 3 << '\n';
		}
	}
} 
