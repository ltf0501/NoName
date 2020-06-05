#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	vector<double> a(5);
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	double tar; cin >> tar;
	vector<int> ia(5);
	for (int i = 0; i < 4; i++) ia[i] = int(round(a[i] * 100));
	int itar = int(round(tar * 100));
	int l = -1, r = 100000;
	while (r - l > 1) {
		int m = (l + r) / 2;
		auto aa = ia;
		aa[4] = m;
		sort(aa.begin(), aa.end());
		auto fin = aa[1] + aa[2] + aa[3];
		if (fin <= itar * 3) l = m;
		else r = m;
	}
	if (l >= 99999) {
		cout << "infinite\n";
	} else if (l < 0) {
		cout << "impossible\n";
	} else {
		cout << fixed << setprecision(2) << double(l) / 100 << '\n';
	}
}
