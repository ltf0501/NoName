#include <bits/stdc++.h>
using namespace std;
int ans[2];
const double pi = acos(-1.0);
int flr(double x) {
  if (x >= 0) return (int)x;
  return (int)x - 1;
}
int cal(int deg, int d) {
  double a = 1.0 * d * cos(deg * pi / 180.0);
  double b = 1.0 * d * sin(deg * pi / 180.0);
  double x = a - b / sqrt(3);
  double y = 2 * b / sqrt(3);
  //	printf("%.3f %.3f %.3f %.3f\n",a,b,x,y);
  //	printf("%.3f\n",(x-flr(x))+(y-flr(y)));
  if ((flr(x) + flr(y)) & 1) {
    if ((flr(x) & 1) ^ ((x - flr(x)) + (y - flr(y)) > 1.0))
      return 2;
    else
      return 1;
  } else {
    if ((flr(x) & 1) ^ ((x - flr(x)) + (y - flr(y)) > 1.0))
      return 3;
    else
      return 0;
  }
}
int main() {
  for (int i = 0; i < 2; i++) {
    char c[5];
    int degree, dis;
    scanf("%s%d%d", c, &degree, &dis);
    if (c[0] == 'C')
      degree += 60;
    else if (c[0] == 'D')
      degree += 120;
    ans[i] = cal(degree, dis);
    // printf("ans[%d] = %d\n",i,ans[i]);
  }
  puts(ans[0] == ans[1] ? "YES" : "NO");
  return 0;
}
