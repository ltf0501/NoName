#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int s; cin >> s;
	string ans, ans0;
	int i;
	for (i = 2; s >= i; s -= i, i = i == 1 ? 2 : 1) {
		ans.push_back(i + '0');
	}
	if (s) {
		if (ans.empty() || ans.back() != (s + '0')) {
			ans.push_back(s + '0');
		} else if (ans[0] != (s + '0')) {
			ans0.push_back(s + '0');
		}
	}
	cout << ans0 << ans << '\n';
}
