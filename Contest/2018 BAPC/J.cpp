#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	double a, b, c, d;
	cin >> a >> b >> c >> d;
	double s = (a + b + c + d) / 2;
	cout << fixed << setprecision(12) << sqrt((s - a) * (s - b) * (s - c) * (s - d)) << '\n';
	return 0;
}

