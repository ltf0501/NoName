#include <bits/stdc++.h>
using namespace std;
#define maxn 50010
const double INF = 1e18;
struct P {
  double x, y;
};
P operator+(P a, P b) { return {a.x + b.x, a.y + b.y}; }
P operator-(P a, P b) { return {a.x - b.x, a.y - b.y}; }
P operator*(P a, double b) { return {a.x * b, a.y * b}; }
P operator/(P a, double b) { return {a.x / b, a.y / b}; }
P a[maxn];
double dot(P a, P b) { return a.x * b.x + a.y * b.y; }
double cross(P a, P b) { return a.x * b.y - a.y * b.x; }
double dis(P b, P c) {
  return sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
}
P cal(P a, P b, P c) {
  P v = c - b;
  return b + v * (dot(v, a - b) / dot(v, v));
}
P intersect(P a, P b, P c, P d) {
  P u = a - c;
  P v = b - a, w = d - c;
  double t = cross(w, u) / cross(v, w);
  return a + v * t;
}
int main() {
  freopen("flags.in", "r", stdin);
  int t;
  scanf("%d", &t);
  int cas = 0;
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    printf("Case %d:\n", ++cas);
    int q;
    scanf("%d", &q);
    while (q--) {
      P p, q;
      scanf("%lf%lf%lf%lf", &p.x, &p.y, &q.x, &q.y);
      P r;
      double ans = INF;
      for (int i = 0; i < n; i++) {
        P s = a[i], t = a[(i + 1) % n];
        P p_0 = cal(p, s, t) * 2 - p;
        double d = dis(p_0, q);
        //			printf("p_0 = (%lf,%lf) d =
        //%lf\n",p_0.x,p_0.y,d);
        if (d < ans) {
          ans = d;
          r = intersect(p_0, q, s, t);
        }
      }
      printf("%.7lf %.7lf %.7lf\n", ans, r.x, r.y);
    }
  }

  return 0;
}
