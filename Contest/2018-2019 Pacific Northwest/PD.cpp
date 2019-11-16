#include <bits/stdc++.h>
using namespace std;
#define maxn 105
bool vis[maxn << 1][maxn];
struct frac {
  int n, m;
  frac() { n = 0, m = 1; }
  frac(int _n, int _m) {
    n = _n, m = _m;
    int g = __gcd(n, m);
    n /= g, m /= g;
    if (m < 0) n = -n, m = -m;
  }
  frac operator+(const frac &rhs) const {
    return frac(m * rhs.n + n * rhs.m, m * rhs.m);
  }
  frac operator-(const frac &rhs) const {
    return frac(n * rhs.m - m * rhs.n, m * rhs.m);
  }
  frac operator*(const frac &rhs) const { return frac(n * rhs.n, m * rhs.m); }
  frac operator*(const int rhs) const { return frac(n * rhs, m); }
  frac operator/(const frac &rhs) const { return frac(n * rhs.m, m * rhs.n); }
  frac operator/(const int rhs) const { return frac(n, m * rhs); }
  double val() { return (double)n / (double)m; }
  void print() { printf("%d/%d\n", n, m); }
};
int n, m, a, b, c, d, r;
frac tmp;
void dfs(frac t, double &A, double &B) {
  //	t.print();
  if (vis[t.n + 100][t.m]) {
    tmp = frac(t.n, t.m);
    A = 0.0, B = 1.0;
    return;
  }
  vis[t.n + 100][t.m] = 1;
  double tmp_A = 0.0, tmp_B = 0.0;
  if (t.n > 0) {
    dfs(frac(1, 1) - (t * 2), tmp_A, tmp_B);
    A = (double)c / (double)r;
    B = (double)d / (double)r + t.val() * t.val();
    A = A + (B * tmp_A);
    B = B * tmp_B;
  } else {
    dfs(frac(-1, 1) - (t * 2), tmp_A, tmp_B);
    A = (double)a / (double)r;
    B = (double)b / (double)r + t.val() * t.val();
    A = A + (B * tmp_A);
    B = B * tmp_B;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(vis, 0, sizeof(vis));
    scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &r);
    frac t(n, m);
    double A = 0.0, B = 0.0;
    //		A.print(),B.print();
    dfs(t, A, B);
    //	A.print(),B.print();
    A = 0.0, B = 0.0;
    memset(vis, 0, sizeof(vis));
    //		printf("tmp = ");tmp.print();
    dfs(tmp, A, B);
    double tt = A / (1.0 - B);
    A = 0.0, B = 0.0;
    dfs(t, A, B);
    double ans = A + (B * tt);
    printf("%.9f\n", ans);
  }
  return 0;
}
