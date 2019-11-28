#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
#define F first
#define S second
const int N = 60;
const double pi = acos(-1);
pair<double, double> p[N], q;
double r[N], theta[N];
double dis(pair<double, double> a, pair<double, double> b) {
  double x = a.F - b.F, y = a.S - b.S;
  return sqrt(x * x + y * y);
}
double dot(pair<double, double> a, pair<double, double> b) {
  return a.F * b.F + a.S * b.S;
}
void solve() {
  int n;
  double ans = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].F, &p[i].S);
  scanf("%lf%lf", &q.F, &q.S);
  for (int i = 1; i <= n; i++) r[i] = dis(p[i], q);
  p[0] = p[n];
  p[n + 1] = p[1];
  for (int i = 1; i <= n; i++) {
    theta[i] = acos(dot({p[i + 1].F - p[i].F, p[i + 1].S - p[i].S},
                        {p[i].F - p[i - 1].F, p[i].S - p[i - 1].S}) /
                    (dis(p[i], p[i + 1]) * dis(p[i], p[i - 1])));
  }
  for (int i = 1; i <= n; i++) ans += theta[i] * r[i];
  printf("%.3lf\n", ans);
  return;
}
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }
}
