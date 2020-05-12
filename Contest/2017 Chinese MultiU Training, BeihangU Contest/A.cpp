#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int x;
	int cas = 0;
	while(cin >> x) {
		int k = int(1.0 * x / log2(10));
		cout << "Case #" << ++cas << ": " << k << '\n';
	}
	return 0;
} 
