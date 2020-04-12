#include <bits/stdc++.h>
using namespace std;
#define PB push_back

constexpr int kN = int(1E2 + 10);
string sa[kN], sb[kN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	vector<tuple<int, int, int>> mx, mn;
	vector<int> va, vb;
	int n, m, h, tmp;
	cin >> n >> m >> h;
	va.reserve(m);
	vb.reserve(h);
	mx.reserve(n * m * h);
	mn.reserve(n * m * h);
	for (int i = 0; i < n; i++) cin >> sa[i];
	for (int i = 0; i < n; i++) cin >> sb[i];
	for (int i = 0; i < n; i++) {
		va.clear();
		vb.clear();
		for (int j = 0; j < m; j++) if (sa[i][j] == '1') va.PB(j);
		for (int j = 0; j < h; j++) if (sb[i][j] == '1') vb.PB(j);
		if (va.empty() ^ vb.empty()) {
			cout << -1 << '\n';
			return 0;
		}
		for (int j : va) for (int k : vb) mx.PB({i, j, k});
		if (va.size() < vb.size()) {
			tmp = int(vb.size()) - int(va.size());
			for (int j = 0; j < tmp; j++) mn.PB({i, va[0], vb[j]});
			for (int j = 0; j < va.size(); j++) mn.PB({i, va[j], vb[j + tmp]});
		}
		else {
			tmp = int(va.size()) - int(vb.size());
			for (int j = 0; j < tmp; j++) mn.PB({i, va[j], vb[0]});
			for (int j = 0; j < vb.size(); j++) mn.PB({i, va[j + tmp], vb[j]});
			
		}
	}
	cout << int(mx.size()) << '\n';
	for (tuple<int, int, int> i : mx) cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << '\n';
	cout << int(mn.size()) << '\n';
	for (tuple<int, int, int> i : mn) cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << '\n';
} 
