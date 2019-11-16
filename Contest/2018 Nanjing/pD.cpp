#include <bits/stdc++.h>
using namespace std;
double a[101], b[101], c[101];
int n;
double cost(double x, double y, double z) {
  double ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, pow(x - a[i], 2) + pow(y - b[i], 2) + pow(z - c[i], 2));
  }
  return ans;
}
int main() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
  mt19937 rng;
  uniform_real_distribution<double> dis(0, 3.141592653589 * 2);
  uniform_real_distribution<double> dis1(0, 1);
  uniform_real_distribution<double> dis2(0, 3.141592653589);
  double x = 0, y = 0, z = 0, cc = cost(x, y, z), ans = cc;
  int cnt = 0;
  for (double temp = 1E5; temp > 1E-4; temp *= 0.99999) {
    double angle = dis(rng), a2 = dis2(rng);
    double nx = x + temp * cos(angle), ny = y + temp * sin(angle) * cos(a2),
           nz = z + temp * sin(angle) * sin(a2);
    double ncost = cost(nx, ny, nz);
    double delta = cc - ncost;
    if (delta > 0 || dis1(rng) < exp(delta / temp)) {
      tie(x, y, z) = make_tuple(nx, ny, nz);
      cc = ncost;
      ans = min(ans, cc);
    }
    ++cnt;
  }
  cerr << cnt << endl;
  cout << fixed << setprecision(20) << sqrt(ans) << '\n';
}
