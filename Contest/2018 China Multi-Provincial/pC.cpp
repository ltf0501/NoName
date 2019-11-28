#include <bits/stdc++.h>
using namespace std;
 
int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int tt = 1; tt <= t; tt++) {
		cout << "Case #" << tt << ": ";
		int n, m; cin >> n >> m;
		string str1, str2; cin >> str1 >> str2;
		string str3; cin >> str3;
		for (char c : str3) {
			int id = c - 'A';
			id = (id + (str1[0] - str2[0]) + 26) % 26;
			cout << char(id + 'A');
		}
		cout << '\n';
	}
}
