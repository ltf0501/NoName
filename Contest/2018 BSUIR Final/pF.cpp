#pragma GCC optimize("O3", "unroll-loops", "fast-math")
#pragma GCC target("avx2,avx")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100010, kMod = 1'000'000'007, kC = 30;

struct matrix {
  int64_t a[4][4];
  matrix() {}
  matrix(bool f) {
    memset(a, 0, sizeof(a));
    if (f)
      for (int i = 0; i < 4; i++) a[i][i] = 1;
  }
};
matrix mul(matrix a, matrix b) {
  matrix ans(false);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      for (int k = 0; k < 4; k++) ans.a[i][j] += a.a[i][k] * b.a[k][j] % kMod;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) ans.a[i][j] %= kMod;
  return ans;
}

matrix Pow(matrix a, int b) {
  matrix ans(1);
  while (b) {
    if (b & 1) ans = mul(ans, a);
    a = mul(a, a);
    b >>= 1;
  }
  return ans;
}

static inline void Add(int64_t &a, int64_t b) { a = (a + b) % kMod; }

static inline int64_t PowMod(int64_t x, int e) {
  if (!e) return 1;
  auto t = PowMod(x, e >> 1);
  t = t * t % kMod;
  if (e & 1) return t * x % kMod;
  return t;
}
int arr[kN], val[kC][kC][4];
bool b[kN][kC];
int64_t dp[2][4];

int main() {
  cin.tie(0), ios_base::sync_with_stdio(0);
  int64_t ans = 0, n, x, y;
  cin >> n >> x >> y;
  int64_t prob = x * PowMod(y, kMod - 2) % kMod,
          prob_inv = (y - x) * PowMod(y, kMod - 2) % kMod;
  matrix A(0), B(0), C(0), tmp;
  for (int i = 0; i < n; i++) cin >> arr[i];
  for (int j = 0; j < kC; j++)
    for (int i = 0; i < n; i++) b[i][j] = !!(arr[i] & (1 << j));
  for (int i = 0; i < kC; i++)
    for (int j = i + 1; j < kC; j++)
      for (int k = 0; k < n; k++)
        if (b[k][i]) {
          if (b[k][j])
            val[i][j][3]++;
          else
            val[i][j][2]++;
        } else if (b[k][j])
          val[i][j][1]++;
  for (int i = 0; i < 4; i++) A.a[i][i] = prob_inv;
  for (int i = 0; i < 4; i++) B.a[i][i] = prob_inv;
  for (int i = 0; i < 4; i++) C.a[i][i] = prob_inv;
  A.a[0][1] = A.a[1][0] = A.a[2][3] = A.a[3][2] = prob;
  B.a[0][2] = B.a[2][0] = B.a[1][3] = B.a[3][1] = prob;
  C.a[0][3] = C.a[1][2] = C.a[2][1] = C.a[3][0] = prob;
  for (int i = 0; i < kC; i++) {
    int j = i;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int k = 0; k < n; k++) {
      int bi = !!(arr[k] & (1 << i));
      int bj = !!(arr[k] & (1 << j));
      if (bi || bj) {
        int idx = bi << 1 | bj;
        for (int ii = 0; ii < 4; ii++) {
          dp[~k & 1][ii] = (1LL * dp[k & 1][ii ^ idx] * prob +
                            1LL * dp[k & 1][ii] * prob_inv) %
                           kMod;
        }
      } else {
        dp[~k & 1][0] = dp[k & 1][0];
        dp[~k & 1][1] = dp[k & 1][1];
        dp[~k & 1][2] = dp[k & 1][2];
        dp[~k & 1][3] = dp[k & 1][3];
      }
    }
    if (i != j) {
      Add(ans, 1LL * dp[n & 1][3] * (1 << (i + 1)) % kMod * (1 << j) % kMod);
    } else {
      Add(ans, 1LL * dp[n & 1][3] * (1 << i) % kMod * (1 << j) % kMod);
    }
  }
  ans %= kMod;
  for (int i = 0; i < kC; i++)
    for (int j = i + 1; j < kC; j++) {
      tmp = mul(mul(Pow(A, val[i][j][1]), Pow(B, val[i][j][2])),
                Pow(C, val[i][j][3]));
      ans += tmp.a[3][0] * (1 << (i + 1)) % kMod * (1 << j) % kMod;
    }
  cout << ans % kMod << '\n';
}
