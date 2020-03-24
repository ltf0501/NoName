#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		double sum = 0;
		vector<int> w(n);
		for (int i = 0; i < n; i++) {
			cin >> w[i];
			sum += w[i];
		}
		for (int i = 0; i < n; i++) {
			cout << fixed << setprecision(10) << w[i] + 1.0 * k * w[i] / sum << ' ';
		}
	}
} 
