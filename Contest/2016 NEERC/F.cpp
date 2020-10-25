#include <bits/stdc++.h>
using namespace std;

int main() {
freopen("foreign.in", "r", stdin);	
freopen("foreign.out", "w", stdout);	
	string s; cin >> s;
	reverse(s.begin(), s.end());
	double val[2] = {};
	int k = 0;
	double cur_val = 0;
	for (char c : s) {
		int kind = c == 'W';
		cur_val = val[kind] / (k + 1);
		//cerr << cur_val << '\n';
		val[!kind] += k + 1;
		val[kind] += cur_val;
		val[!kind] += cur_val;
		++k;
	}
	cout << setprecision(20) << fixed << cur_val << '\n';
} 
