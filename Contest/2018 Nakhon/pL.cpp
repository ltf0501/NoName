#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
int c[maxn][maxn];
int dp[2][maxn][maxn];
int up[maxn][maxn], le[maxn][maxn];
static inline char getRawChar() {
  static char buf[1 << 16], *p = buf, *end = buf;
  if (p == end) {
    if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
    p = buf;
  }
  return *p++;
}
char getChar() {
  char c;
  while (!isdigit(c = getRawChar()))
    ;
  return c;
}
int readInt() {
  char c;
  int n = 0;
  while (!isdigit(c = getRawChar()))
    ;
  do {
    n = n * 10 + (c - '0');
  } while ((c = getRawChar()) && isdigit(c));
  return n;
}
int main() {
  int T = readInt();
  while (T--) {
    int n = readInt(), m = readInt();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) c[i][j] = getChar() == '1';
    for (int i = 1; i <= n; i++) {
      int cur = 0;
      for (int j = 1; j <= m; j++) {
        le[i][j] = cur;
        if (c[i][j] == 1) cur = j;
      }
    }
    for (int j = 1; j <= m; j++) {
      int cur = 0;
      for (int i = 1; i <= n; i++) {
        up[i][j] = cur;
        if (c[i][j] == 1) cur = i;
      }
    }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (c[i][j] == 1)
          dp[0][i][j] = 0;
        else
          dp[0][i][j] =
              min({dp[0][i - 1][j], dp[0][i][j - 1], dp[0][i - 1][j - 1]}) + 1;
      }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (c[i][j] == 1) {
          dp[1][i][j] =
              min({dp[0][i - 1][j - 1] + 1, i - up[i][j], j - le[i][j]});
        } else {
          int t1 = min({dp[1][i - 1][j - 1] + 1, i - up[i][j], j - le[i][j]});
          int l = le[i][j], u = up[i][j];
          int ll = le[i][l], uu = up[u][j];
          int tmp;
          int x = j - l, a = l - ll;
          int y = i - u, b = u - uu;
          if (x > y) swap(x, y), swap(a, b);
          tmp = min(y, a + x);
          int t2 = min({dp[0][i - 1][j - 1] + 1, tmp});
          dp[1][i][j] = max(t1, t2);
        }
      }
    int ans = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) ans = max(ans, dp[1][i][j]);
    printf("%d\n", ans);
  }
  return 0;
}
