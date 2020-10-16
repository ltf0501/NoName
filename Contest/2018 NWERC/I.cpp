#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	vector<int> cs(n);
	for (int i = 0; i < n; i++) cin >> cs[i];
	sort(cs.begin(), cs.end());
	double ans = 1.0;
	for (int i = n; i > 0; i--) {
		if (cs[i - 1] > i) {
			cout << "-1\n";
			exit(0);
		}
		ans = min(ans, 1.0 * cs[i - 1] / i);
	}
	cout << ans << '\n';
} 
