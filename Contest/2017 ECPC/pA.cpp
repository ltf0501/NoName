#include <stdio.h>
const int N = 5e1 + 10;
const int K = 3e3 + 10;
int n, orix, oriy;
double p;
double val3[N][K], val1[N][K], val2[N][N][K];
double dp1(int pos, int k) {
  if (k == 0) return pos == orix ? 1 : 0;
  if (val1[pos][k] >= 0) return val1[pos][k];
  if (pos == 0)
    return val1[pos][k] = (p * (n - 2) / (n - 1) + (1 - p)) * dp1(pos, k - 1) +
                          (p * 1.0 / (n - 1)) * dp1(pos + 1, k - 1);
  else if (pos == n - 1)
    return val1[pos][k] = (p * (n - 2) / (n - 1) + (1 - p)) * dp1(pos, k - 1) +
                          (p * 1.0 / (n - 1)) * dp1(pos - 1, k - 1);
  else
    return val1[pos][k] = (p * (n - 3) / (n - 1) + (1 - p)) * dp1(pos, k - 1) +
                          (p * 1.0 / (n - 1)) *
                              (dp1(pos - 1, k - 1) + dp1(pos + 1, k - 1));
}
double dp2(int x, int y, int k) {
  if (k == 0) return x == orix && y == oriy ? 1 : 0;
  if (val2[x][y][k] >= 0) return val2[x][y][k];
  if (x == 0) {
    if (y == 1)
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x + 1, y - 1, k - 1) + dp2(x, y + 1, k - 1)) +
                 (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    else if (y == n - 1)
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x + 1, y, k - 1) + dp2(x, y - 1, k - 1)) +
                 (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    else
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x + 1, y, k - 1) + dp2(x, y - 1, k - 1) +
                      dp2(x, y + 1, k - 1)) +
                 (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
  } else if (x == n - 1) {
    if (y == n - 2)
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x - 1, y + 1, k - 1) + dp2(x, y - 1, k - 1)) +
                 (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    else if (y == 0)
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x - 1, y, k - 1) + dp2(x, y + 1, k - 1)) +
                 (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    else
      return val2[x][y][k] =
                 (p * 1.0 / (n - 1)) *
                     (dp2(x - 1, y, k - 1) + dp2(x, y + 1, k - 1) +
                      dp2(x, y - 1, k - 1)) +
                 (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
  } else {
    if (y == 0) {
      if (x == 1)
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y + 1, k - 1) + dp2(x + 1, y, k - 1)) +
                   (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
      else
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y, k - 1) + dp2(x + 1, y, k - 1) +
                        dp2(x, y + 1, k - 1)) +
                   (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    } else if (y == n - 1) {
      if (x == n - 2)
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y, k - 1) + dp2(x + 1, y - 1, k - 1)) +
                   (p * (n - 3) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
      else
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y, k - 1) + dp2(x + 1, y, k - 1) +
                        dp2(x, y - 1, k - 1)) +
                   (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    } else {
      if (x == y + 1)
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y + 1, k - 1) + dp2(x + 1, y, k - 1) +
                        dp2(x, y - 1, k - 1)) +
                   (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
      else if (x == y - 1)
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x + 1, y - 1, k - 1) + dp2(x - 1, y, k - 1) +
                        dp2(x, y + 1, k - 1)) +
                   (p * (n - 4) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
      else
        return val2[x][y][k] =
                   (p * 1.0 / (n - 1)) *
                       (dp2(x - 1, y, k - 1) + dp2(x + 1, y, k - 1) +
                        dp2(x, y + 1, k - 1) + dp2(x, y - 1, k - 1)) +
                   (p * (n - 5) / (n - 1) + (1 - p)) * dp2(x, y, k - 1);
    }
  }
}
double dp3(int now, int k) {
  if (k == 0) return now == 0 ? 1 : 0;
  if (val3[now][k] >= 0) return val3[now][k];
  return val3[now][k] = p * dp3(1 - now, k - 1) + (1 - p) * dp3(now, k - 1);
}
int main() {
  freopen("assessment.in", "r", stdin);
  int t, k;
  scanf("%d", &t);
  double ans;
  for (int o = 1; o <= t; o++) {
    scanf("%d%lf%d%d%d", &n, &p, &orix, &oriy, &k);
    if (n == 1)
      printf("Case %d: 1.00000\n", o);

    else if (n == 2) {
      for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++) val3[i][j] = val1[i][j] = -1;
      if (orix == oriy)
        printf("Case %d: %.5lf\n", o, dp1(orix, k));
      else
        printf("Case %d: %.5lf\n", o, dp3(1, k));
    } else if (orix == oriy) {
      for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++) val1[i][j] = -1;
      printf("Case %d: %.5lf\n", o, dp1(orix, k));
    } else {
      for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
          for (int a = 0; a < K; a++) val2[i][j][a] = -1;
      printf("Case %d: %.5lf\n", o, dp2(oriy, orix, k));
    }
  }
  return 0;
}
