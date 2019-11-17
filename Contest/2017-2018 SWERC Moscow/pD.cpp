#include <bits/stdc++.h>
using namespace std;
const int maxn = 51;
const int maxk = 201;
char s[maxn], c[maxk << 1][maxn];
int len[maxk << 1], cost[maxk << 1];
int dp[maxn];
int f[maxn][maxn][maxk << 1][maxn];
int g[maxn][maxn];
int main() {
  scanf("%s", s);
  int n = strlen(s);
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%s %d", c[i], &cost[i]);
    len[i + m] = len[i] = strlen(c[i]);
    cost[i + m] = cost[i];
    for (int j = 0; j < len[i]; j++) c[i + m][j] = c[i][j];
    reverse(c[i + m], c[i + m] + len[i]);
  }
  m <<= 1;
  memset(f, -1, sizeof(f));
  memset(g, -1, sizeof(g));
  for (int i = 0; i <= n; i++) g[i][i] = 0;
  for (int l = 1; l <= n; l++) {
    for (int i = 0; i + l <= n; i++) {
      int j = i + l;  // [i, j)
      // printf("i = %d, j = %d\n", i, j);
      for (int k = 0; k < m; k++) {
        for (int y = 0; y < len[k]; y++) {
          for (int ii = i; ii < j; ii++)
            if (s[ii] == c[k][y]) {
              if (g[i][ii] != -1) {
                if (y + 1 != len[k] && f[ii + 1][j][k][y + 1] != -1)
                  f[i][j][k][y] =
                      max(f[i][j][k][y], f[ii + 1][j][k][y + 1] + g[i][ii]);
                else if (y + 1 == len[k] && g[ii + 1][j] != -1)
                  f[i][j][k][y] =
                      max(f[i][j][k][y], g[ii + 1][j] + g[i][ii] + cost[k]);
              }
            }
          if (y == 0 && f[i][j][k][0] != -1) {
            g[i][j] = max(g[i][j], f[i][j][k][0]);
          }
          // printf("%d ", f[i][j][k][y]);
        }
        // puts("");
      }
      // puts("--------------");
    }
  }
  // for(int i = 0; i <= n; i++) {
  //	for(int j = 0; j <= n; j++) printf("%d ", g[i][j]);
  //	puts("");
  //}
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];
    for (int j = 0; j < n; j++)
      if (g[j][i] != -1) dp[i] = max(dp[i], dp[j] + g[j][i]);
  }
  printf("%d\n", dp[n]);
  return 0;
}
