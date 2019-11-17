#include <stdio.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define PB push_back
#define F first
#define S second

const int MOD = 1000000000;
const int N = 5e2 + 10;
struct matrix {
  long long int a[N][N];
  int size;
  matrix() {}
  matrix(int n, int k) {
    size = n;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) a[i][j] = 0;
    if (k == 1)
      for (int i = 0; i < n; i++) a[i][i] = 1;
  }
  void out() {
    return;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        printf("%d ", a[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    return;
  }
};

matrix mul(matrix a, matrix b) {
  int n = a.size;
  matrix temp(n, 0);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        temp.a[i][j] = (temp.a[i][j] + a.a[i][k] * b.a[k][j]) % MOD;
  return temp;
}
matrix pow(matrix a, long long int b) {
  matrix ans(a.size, 1);
  while (b) {
    if (b & 1) ans = mul(ans, a);
    a = mul(a, a);
    b >>= 1;
  }
  return ans;
}
long long int trans(int u, int v, int n) {
  long long int ans = 0, tt;
  queue<pair<int, int>> q;
  int temp;
  pair<int, int> nxt;
  vector<int> ve;
  q.push({u, 0});
  while (!q.empty()) {
    nxt = q.front();
    q.pop();
    for (int i = nxt.S; i < n - 1; i++)
      if (!(nxt.F & (1 << i)) && !(nxt.F & (1 << (i + 1))))
        q.push({nxt.F ^ (1 << i) ^ (1 << (i + 1)), i + 2});
    ve.PB(nxt.F);
  }
  for (int i : ve) {
    tt = 1;
    for (int j = 0; j < n; j++) {
      if ((1 << j) & v) {
        if ((1 << j) & i) tt = 0;
      }
    }
    ans += tt;
  }
  ans %= MOD;
  return ans;
}
int main() {
  int n, tot;
  long long int m, ans = 0;
  matrix a;
  scanf("%d%lld", &n, &m);
  tot = 1 << n;
  a.size = tot;
  for (int i = 0; i < tot; i++)
    for (int j = 0; j < tot; j++) a.a[i][j] = 0;
  for (int i = 0; i < tot; i++)
    for (int j = 0; j < tot; j++) {
      a.a[i][j] = trans(i, j, n);
    }
  /*
  a.a[0][0]=2;
  a.a[0][1]=1;
  a.a[0][2]=1;
  a.a[0][3]=1;
  a.a[1][0]=1;
  a.a[1][1]=0;
  a.a[1][2]=1;
  a.a[1][3]=0;
  a.a[2][0]=1;
  a.a[2][1]=1;
  a.a[2][2]=0;
  a.a[2][3]=0;
  a.a[3][0]=1;
  a.a[3][1]=0;
  a.a[3][2]=0;
  a.a[3][3]=0;
  */
  a.out();
  a = pow(a, m);
  a.out();
  ans = a.a[0][0];
  printf("%lld\n", ans);
}
