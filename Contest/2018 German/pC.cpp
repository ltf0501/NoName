#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 1e3 + 10;
vector<pair<int, int>> graph[N];
int dis[N];
int dfs(int pos) {
  if (dis[pos] >= 0) return dis[pos];
  dis[pos] = 0;
  for (pair<int, int> i : graph[pos]) dis[pos] = max(dis[pos], i.S + dfs(i.F));
  return dis[pos];
}
int main() {
  int ans = 0, n, m, l, r, c;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) dis[i] = -1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &l, &r, &c);
    graph[l].PB({r, c});
  }
  for (int i = 1; i <= n; i++) ans = max(ans, dfs(i));
  printf("%d\n", ans);
}
