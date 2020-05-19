#include <bits/stdc++.h>
using namespace std;

using D = long double;

D Cross(pair<D, D> p0, pair<D, D> p1, pair<D, D> p2) {
	p1.first -= p0.first;
	p1.second -= p0.second;
	p2.first -= p0.first;
	p2.second -= p0.second;
	return p1.first * p2.second - p1.second * p2.first;
}

D Area(vector<pair<D, D>> &p) {
	D res = 0;
	for (int i = 1; i < int(p.size()) - 1; i++) {
		res += Cross(p[0], p[i], p[i + 1]);
	}
	return abs(res * 0.5);
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	D ans = 0;
	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		vector<pair<D, D>> ps(p);
		for (int j = 0; j < p; j++) cin >> ps[j].first >> ps[j].second;
		ans += Area(ps);
	}
	cout << int64_t(floorl(ans)) << '\n';
} 
