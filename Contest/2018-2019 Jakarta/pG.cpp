bool debug = false;
#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N = 5e2 + 10;
const int INF = 1e9 + 10;
int main() {
  int n, m, l, r, k = INF, deg[N], to[N], ans = -1, pl, pr;
  bool graph[N][N];
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) deg[i] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) graph[i][j] = true;
  for (int i = 1; i <= n; i++) graph[i][i] = false;
  while (m--) {
    scanf("%d%d", &l, &r);
    deg[l]++;
    deg[r]++;
    graph[l][r] = graph[r][l] = false;
  }
  deg[0] = -1;
  for (int i = 1; i <= n; i++) to[i] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (deg[to[i]] < deg[j] && graph[i][j]) to[i] = j;
  while (true) {
    ans = -1;
    for (int i = 1; i <= n; i++)
      if (to[i] > 0 && deg[i] + deg[to[i]] > ans) {
        ans = deg[i] + deg[to[i]];
        pl = i;
        pr = to[i];
      }
    if (ans < 0) break;
    if (debug) {
      printf("ans=%d\n", ans);
      printf("deg::");
      for (int i = 1; i <= n; i++) printf("%d ", deg[i]);
      printf("\nto::");
      for (int i = 1; i <= n; i++) printf("%d ", to[i]);
      printf("\n");
    }
    k = min(ans, k);
    graph[pl][pr] = graph[pr][pl] = false;
    to[pl] = to[pr] = 0;
    for (int i = 1; i <= n; i++)
      if (graph[pl][i] && deg[to[pl]] < deg[i]) to[pl] = i;
    for (int i = 1; i <= n; i++)
      if (graph[pr][i] && deg[to[pr]] < deg[i]) to[pr] = i;
    deg[pl]++;
    deg[pr]++;
  }
  printf("%d\n", k);
}
