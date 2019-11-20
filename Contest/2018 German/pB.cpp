#include <math.h>
#include <stdio.h>
using namespace std;
double dist(double ax, double ay, double bx, double by) {
  double x = ax - bx, y = ay - by;
  return sqrt(x * x + y * y);
}
int main() {
  double x, y, dis, A, B, C, ax, ay, bx, by, cx, cy, dx, dy, r, d, cr, theta,
      da, db, ans;
  scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &ax, &ay, &bx, &by, &cx, &cy, &cr,
        &dx, &dy, &r);
  A = ay - by;
  B = bx - ax;
  C = ax * A + ay * B;
  d = abs((A * dx + B * dy - C)) / sqrt(A * A + B * B);
  da = dist(ax, ay, dx, dy);
  db = dist(bx, by, dx, dy);
  theta = acos(d / da) + acos(d / db) - acos(r / da) - acos(r / db);
  ans = sqrt(da * da - r * r) + sqrt(db * db - r * r) + r * theta;
  printf("%.20lf\n", ans);
}
