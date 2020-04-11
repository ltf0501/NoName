#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const double eps = 1e-9;

int n, a, b;
int x[kN];
double v[kN];

double sol(double a, double b, double c) {
    return (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> a >> b;	
	for(int i = 0; i < n; i++) cin >> x[i] >> v[i];
	for(int i = n - 2; i >= 0; i--) v[i] = min(v[i], sqrt(2LL * b * (x[i + 1] - x[i]) + v[i + 1] * v[i + 1]));

	int xx = 0;
	double vv = 0;
	double ans = 0;

	for(int i = 0; i < n; i++) {
		double nextv = sqrt(2LL * a * (x[i] - xx) + vv * vv);
		if(nextv <= v[i] + eps) {
			ans += (nextv - vv) / a;
			vv = nextv;
		}
		else {
			double t = sol(double(a * a + a * b), 2.0 * vv * (a + b), vv * vv - v[i] * v[i] + 2.0 * b * xx - 2.0 * b * x[i]);
			double mxv = vv + a * t;
			t += (mxv - v[i]) / b;
			ans += t;
			vv = v[i];
		}
		xx = x[i];
	}
	cout << setprecision(15) << ans << '\n';
	return 0;
}
