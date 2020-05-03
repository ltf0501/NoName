#include <bits/stdc++.h>
using namespace std;

using D = __float128;

D lambda[100010], lsa[100010], lsb[100010];
int x[100010], y[100010];

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 0; i <= n; i++) cin >> x[i] >> y[i];
	lambda[0] = D(0.5) * (y[1] - y[0]) / (x[1] - x[0]) + D(-0.5) * (y[1] - y[0]) / (x[1] - x[0]);
	for (int i = 1; i < n; i++) {
		lambda[i] = D(-0.5) * (y[i] - y[i - 1]) / (x[i] - x[i - 1]) + D(0.5) * (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
	}
	lambda[n] = D(0.5) * (y[n] - y[n - 1]) / (x[n] - x[n - 1]) + D(-0.5) * (y[n] - y[n - 1]) / (x[n] - x[n - 1]);
	for (int i = 1; i <= n + 1; i++) {
		lsa[i] = lsa[i - 1] + lambda[i - 1];
		lsb[i] = lsb[i - 1] + lambda[i - 1] * x[i - 1];
	}
	bool ok = true;
	for (int i = 0; i <= n; i++) {
		D t = 0;
		t -= ((lsa[n + 1] - lsa[i + 1]) - (lsa[i])) * x[i];
		t += (lsb[n + 1] - lsb[i + 1]) - lsb[i];
		ok &= abs((long double)(t - y[i])) < 1e-8;
	}
	cout << ((ok) ? "Yes\n" : "No\n");
} 
