#include <bits/stdc++.h>
using namespace std;

int64_t Solve(string s) {
	int n = int(s.size());
	s = s + s;
	vector<int> suma(s.size() + 1);
	vector<int> sumb(s.size() + 1);
	vector<int> sumc(s.size() + 1);
	for (int i = 0; i < int(s.size()); i++) {
		suma[i + 1] = suma[i] + (s[i] == 'A');
		sumb[i + 1] = sumb[i] + (s[i] == 'B');
		sumc[i + 1] = sumc[i] + (s[i] == 'C');
	}
	int ca = suma[n], cb = sumb[n], cc = sumc[n];
	int sa = 0, sb = ca, sc = ca + cb;
	int ans = INT_MAX;
	for (int i = 0; i < n; i++) {
		int oka = suma[sa + ca] - suma[sa];
		int okb = sumb[sb + cb] - sumb[sb];
		int okc = sumc[sc + cc] - sumc[sc];
		ans = min(ans, n - oka - okb - okc);
		sa = (sa + 1) % n;
		sb = (sb + 1) % n;
		sc = (sc + 1) % n;
	}
	return ans;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	string s; cin >> s;
	char perm[] = {'A', 'B', 'C'};
	int64_t ans = INT64_MAX;
	do {
		auto ss = s;
		for (char &c : ss) {
			c = perm[c - 'A'];
		}
		ans = min(ans, Solve(ss));
	} while (next_permutation(perm, perm + 3));
	cout << ans << '\n';
} 
