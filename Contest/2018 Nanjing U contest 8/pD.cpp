#include <bits/stdc++.h>
using namespace std;
#define maxn 205
int n, m;
char c[maxn][maxn];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    bool flag = 0;
    if ((n & 1) && (m & 1)) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) putchar('(');
        puts("");
      }
      continue;
    } else if ((n & 1) || (m & 1)) {
      if (m & 1) swap(n, m), flag = 1;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++)
          c[i][j << 1] = '(', c[i][j << 1 | 1] = ')';
      }
    } else {
      if (n > m) swap(n, m), flag = 1;
      if (n == 2) {
        for (int i = 0; i < m; i++) c[0][i] = '(', c[1][i] = ')';
      } else if (n == 4) {
        for (int i = 0; i < m; i++) c[0][i] = '(', c[3][i] = ')';
        for (int i = 0; i < m; i++) {
          if (i < m / 2)
            c[1][i] = ')', c[2][i] = '(';
          else
            c[1][i] = '(', c[2][i] = ')';
        }
      } else {
        for (int i = 0; i < m; i++) c[0][i] = '(', c[n - 1][i] = ')';
        for (int i = 1; i < n - 1; i++) {
          if (i & 1) {
            for (int j = 0; j < m / 2; j++)
              c[i][j << 1] = '(', c[i][j << 1 | 1] = ')';
          } else {
            c[i][0] = '(', c[i][m - 1] = ')';
            for (int j = 0; j < m / 2 - 1; j++)
              c[i][j << 1 | 1] = '(', c[i][(j << 1) + 2] = ')';
          }
        }
      }
    }
    if (!flag) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) putchar(c[i][j]);
        puts("");
      }
    } else {
      for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) putchar(c[i][j]);
        puts("");
      }
    }
  }
  return 0;
}
