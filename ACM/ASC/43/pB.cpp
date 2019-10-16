#include <bits/stdc++.h>
using namespace std;
 
bool sep[100010];
 
int main() {
	cin.tie(nullptr); ios_base::sync_with_stdio(false);
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	int64_t n, k;
	while (cin >> n >> k && n) {
		for (int i = 0; i <= n; i++) sep[i] = false;
		--k;
		for (int i = 0; i < n - 1; i++, k >>= 1) sep[i] = ~k & 1;
		reverse(sep, sep + n - 1);
		//for (int i = 0; i < n; i++) cerr << sep[i];
		//cerr << endl;
		int last = 1;
		for (int i = 1; i <= n; i++) {
			if (sep[i - 1] || i == n) {
				cout << i << ' ';
				for (; last < i; last++) cout << last << ' ';
				last = i + 1;
			}
		}
		cout << '\n';
	}
}
