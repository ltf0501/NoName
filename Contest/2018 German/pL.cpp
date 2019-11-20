#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int n, m;
int a[maxn][maxn];
bool ans[maxn][maxn];
void bye(int i, int j) {
  //	for(int x = 1; x <= n; x++) {
  //		for(int y = 1; y <= m; y++) printf("%d ", ans[x][y]);
  //		puts("");
  //	}
  // printf("i = %d, j = %d\n", i, j);
  puts("impossible");
  exit(0);
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n + 2; i++)
    for (int j = 0; j < m + 2; j++) scanf("%d", &a[i][j]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int num = 0;
      for (int x = i - 2; x <= i; x++)
        for (int y = j - 2; y <= j; y++) {
          if (x < 0 || y < 0) continue;
          if (ans[x][y]) num++;
        }
      if (a[i - 1][j - 1] - num >= 2 || a[i - 1][j - 1] < num)
        bye(i, j);
      else if (a[i - 1][j - 1] - num == 1)
        ans[i][j] = 1;
    }
    for (int j = m; j <= m + 1; j++) {
      int num = 0;
      for (int x = i - 2; x <= i; x++)
        for (int y = j - 1; y <= j + 1; y++) {
          if (x < 0 || y < 0) continue;
          if (ans[x][y]) num++;
        }
      if (a[i - 1][j] != num) bye(i, j);
    }
  }
  for (int i = n; i <= n + 1; i++) {
    for (int j = 0; j < m + 2; j++) {
      int num = 0;
      for (int x = i - 1; x <= i + 1; x++)
        for (int y = j - 1; y <= j + 1; y++) {
          if (x < 0 || y < 0) continue;
          if (ans[x][y]) num++;
        }
      if (a[i][j] != num) bye(i, j);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      putchar(ans[i][j] ? 'X' : '.');
    }
    puts("");
  }
  return 0;
}
