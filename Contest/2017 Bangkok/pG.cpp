bool debug = false;
#include <stdio.h>
const long long int MOD = 1e9 + 7;
struct matrix {
  long long int a[3][3];
  void I() {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) a[i][j] = 0;
    for (int i = 0; i < 3; i++) a[i][i] = 1;
    return;
  }
  void operator*=(const matrix n) {
    matrix temp;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) temp.a[i][j] = a[i][j];
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) a[i][j] = 0;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++) {
          a[i][j] += temp.a[i][k] * n.a[k][j] % MOD;
          a[i][j] %= MOD;
        }
    return;
  }
  void out() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) printf("%lld ", a[i][j]);
      printf("\n");
    }
    return;
  }
};
matrix POW(matrix a, long long int b) {
  matrix ans;
  ans.I();
  while (b) {
    if (b & 1) ans *= a;
    b >>= 1;
    a *= a;
  }
  return ans;
}
matrix A, B;
void pre() {
  A.a[0][0] = 0;
  A.a[0][1] = 1;
  A.a[0][2] = 0;
  A.a[1][0] = 1;
  A.a[1][1] = 1;
  A.a[1][2] = 0;
  A.a[2][0] = 0;
  A.a[2][1] = 0;
  A.a[2][2] = 1;
  B.a[0][0] = 0;
  B.a[0][1] = 1;
  B.a[0][2] = 0;
  B.a[1][0] = 1;
  B.a[1][1] = 1;
  B.a[1][2] = 0;
  B.a[2][0] = 1;
  B.a[2][1] = 1;
  B.a[2][2] = 1;
  return;
}
void solve() {
  long long int l, r, k, n, ans, lans = 0, rans = 0;
  matrix MUL, temp;
  scanf("%lld%lld%lld", &l, &r, &k);
  l = (l - 1) / k;
  r /= k;
  MUL = POW(A, k - 1);
  MUL *= B;
  if (debug) printf("A::\n"), A.out();
  if (debug) printf("B::\n"), B.out();
  if (debug) printf("MUL::\n"), MUL.out();
  temp = POW(MUL, l);
  if (debug) printf("L::\n"), temp.out();
  for (int i = 0; i < 3; i++) lans = (lans + temp.a[i][1]) % MOD;
  temp = POW(MUL, r);
  if (debug) printf("R::\n"), temp.out();
  for (int i = 0; i < 3; i++) rans = (rans + temp.a[i][1]) % MOD;
  if (debug) printf("lans=%lld rans=%lld\n", lans, rans);
  ans = (rans - lans) % MOD;
  if (ans < 0) ans += MOD;
  printf("%lld\n", ans);
  return;
}
int main() {
  int t;
  pre();
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case %d: ", i);
    solve();
  }
}
