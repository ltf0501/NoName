bool debug = false;
#include <stdio.h>
const int N = 5e2 + 10;
const double eps = 1e-9;
int n;
double A[10][N][N], dis[N][N];
double ABS(double x) { return x >= 0 ? x : -x; }
void out(int lv) {
  if (!debug) return;
  printf("out\n");
  for (int i = 0; i < n; i++, printf("\n"))
    for (int j = 0; j <= n; j++) printf("%.3lf ", A[lv][i][j]);
  printf("\n");
  return;
}
void dc(int l, int r, int lv) {
  if (debug) printf("dc(%d,%d)\n", l, r);
  if (l == r) {
    out(lv);
    for (int i = 0; i < n; i++)
      if (i != l) dis[i][l] = A[lv][i][n] / A[lv][i][i];
  } else {
    int mid = (l + r) >> 1;
    double val;
    lv++;
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= n; j++) A[lv][i][j] = A[lv - 1][i][j];
    for (int i = l; i <= mid; i++) {
      for (int j = 0; j < n; j++)
        if (j != i) {
          val = A[lv][j][i] / A[lv][i][i];
          for (int k = 0; k <= n; k++) A[lv][j][k] -= val * A[lv][i][k];
        }
    }
    dc(mid + 1, r, lv);
    for (int i = 0; i < n; i++)
      for (int j = 0; j <= n; j++) A[lv][i][j] = A[lv - 1][i][j];
    for (int i = mid + 1; i <= r; i++) {
      for (int j = 0; j < n; j++)
        if (j != i) {
          val = A[lv][j][i] / A[lv][i][i];
          for (int k = 0; k <= n; k++) A[lv][j][k] -= val * A[lv][i][k];
        }
    }
    dc(l, mid, lv);
  }
  return;
}
int main() {
  int k, m, q, temp, l, r, last;
  double ans;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++) A[0][i][j] = 0;
  while (m--) {
    scanf("%d%d", &l, &r);
    A[0][l][r] -= 1;
    A[0][l][l] += 1;
    A[0][l][n] += 1;
  }
  out(0);
  dc(0, n - 1, 0);
  while (q--) {
    scanf("%d%d", &k, &last);
    k--;
    ans = 0;
    while (k--) {
      scanf("%d", &temp);
      ans += dis[last][temp];
      last = temp;
    }
    printf("%.20lf\n", ans);
  }
}
