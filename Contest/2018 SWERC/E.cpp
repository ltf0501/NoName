#include <bits/stdc++.h>
using namespace std;
const int kN = 1e4 + 10;

string name[kN];
int val[kN];
double mn[kN], mx[kN];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> name[i] >> val[i];
		mn[i] = max(0.0, val[i] - 0.50);
		mx[i] = min(100.0, val[i] + 0.49);
	}
	double Mn = 0, Mx = 0;
	for(int i = 0; i < n; i++) {
		Mn += mn[i], Mx += mx[i];
	}
	if(Mn > 100.0 || Mx < 100.0) return puts("IMPOSSIBLE"), 0;
	for(int i = 0; i < n; i++) {
		cout << name[i] << ' ';
		double tmp_min = max(mn[i], mx[i] - (Mx - 100));
		double tmp_max = min(mx[i], mn[i] + (100 - Mn));
		cout << fixed << setprecision(2);
		cout << tmp_min << ' ' << tmp_max << '\n';
	}
	return 0;
} 
