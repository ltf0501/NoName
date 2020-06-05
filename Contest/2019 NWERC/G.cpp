#include <bits/stdc++.h>
using namespace std;
const int kN = 505;
using D = long double;

int n, k;
D a[kN];

D C[kN][kN], ans[kN];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for(int i = 0; i < n; i++) cin >> a[i];
	if(k == 1) {
		for(int i = 0; i < n; i++) cout << fixed << setprecision(12) << 100.0 / n << ' ';
		cout << '\n';
		return 0;
	}
	
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) ans[i] += a[(i - j + n) % n] * C[n - 1 - j][k - 1];
	}

	for(int i = 0; i < n; i++) cout<< fixed << setprecision(12) << ans[i] / C[n][k] << ' ';
	cout << '\n';
	return 0;
}
