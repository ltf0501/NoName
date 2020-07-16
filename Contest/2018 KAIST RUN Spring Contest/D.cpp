#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int r1, r2, r3, r4, f1, f2, f3, f4, n, k, tr, tf;
	map<string, int> R, F;
	string s;
	cin >> r1 >> r2 >> r3 >> r4 >> f1 >> f2 >> f3 >> f4 >> n;
	for (int i = 1; i <= n; i++) {
		cin >> k >> s;
		if (k == 1) {
			R[s] = i;
			F[s]++;
		}
		else {
			if (R.find(s) == R.end()) cout << "None\n";
			else {
				tr = i - R[s], tf = F[s];
				if (tr <= r1) {
					if (tf <= f1) cout << "New Customer\n";
					else if (tf <= f3) cout << "Potential Loyalist\n";
					else if (tf <= f4) cout << "Loyal Customer\n";
					else cout << "Champion\n";
				}
				else if (tr <= r2) {
					if (tf <= f1) cout << "Promising\n";
					else if (tf <= f3) cout << "Potential Loyalist\n";
					else cout << "Loyal Customer\n";
				}
				else if (tr <= r3) {
					if (tf <= f2) cout << "About to Sleep\n";
					else if (tf <= f3) cout << "Need Attention\n";
					else cout << "Loyal Customer\n";
				}
				else if (tr <= r4) {
					if (tf <= f1) cout << "Lost\n";
					else if (tf <= f2) cout << "Hibernating\n";
					else cout << "About to Leave\n";
				}
				else {
					if (tf <= f2) cout << "Lost\n";
					else if (tf <= f4) cout << "About to Leave\n";
					else cout << "Can't Lose Them\n";
				}
			}
		}
	}

} 
