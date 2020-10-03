#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int a[3]; cin >> a[0] >> a[1] >> a[2];
	int b[2]; cin >> b[0] >> b[1];
	sort(a, a + 3);
	sort(b, b + 2);
	do {
		do {
			if ((2 * a[1] + 2 * a[2]) <= b[0] && (a[0] + a[1] * 2) <= b[1]) {
				cout << "Yes\n";
				return 0;
			}
			if ((3 * a[0] + a[1] + a[2]) <= b[0] && (a[1] + a[2]) <= b[1]) {
				cout << "Yes\n";
				return 0;
			}
		} while (next_permutation(b, b + 2));
	} while (next_permutation(a, a + 3));
	cout << "No\n";
} 
