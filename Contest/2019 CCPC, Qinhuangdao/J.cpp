#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 998244353;

void ZAlg(const string &str, vector<int> &z) {
	int l = 0, r = 0, len = int(str.size());
	for (int i = 0; i < len; i++) {
		if (i > r) {
			l = r = i;
			while (r < len && str[r] == str[r - l]) r++;
			z[i] = r - l;
			--r;
		} else {
			if (z[i - l] < r - i + 1) {
				z[i] = z[i - l];
			} else {
				l = i;
				while (r < len && str[r] == str[r - l]) ++r;
				z[i] = r - l;
				--r;
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int64_t a, b; cin >> a >> b;
	string s; cin >> s;
	reverse(s.begin(), s.end());
	while (s.back() != '.') s.pop_back();
	s.pop_back();
	vector<int> z(s.size());
	ZAlg(s, z);
	int64_t ans = a * int(s.size()) - b * int(s.size());
	for (int l = 1; l < int(s.size()); l++) {
		int p = z[l] + l;
		ans = max(ans, a * p - b * l);
		//cerr << l << ": " << p << '\n';
	}
	cout << ans << '\n';
} 
