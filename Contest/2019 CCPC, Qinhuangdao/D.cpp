#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		while (n % 2 == 0) n /= 2;
		while (n % 5 == 0) n /= 5;
		cout << (n != 1 ? "Yes\n" : "No\n");
	}
} 
