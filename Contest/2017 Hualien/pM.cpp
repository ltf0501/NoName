bool debug = false;
#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
#define PB push_back
const int N = 1e3 + 10;
const int INF = 1e9 + 10;
const int D = 21;
struct edge {
  int to, rev, cap;
  edge(int a, int b, int c) : to(a), rev(b), cap(c) {}
};
int min(int a, int b) { return a > b ? b : a; }
int dep[N], iter[N], went[N];
vector<edge> graph[N];
void addedge(int u, int v, int cap) {
  graph[u].PB(edge(v, (int)graph[v].size(), cap));
  graph[v].PB(edge(u, (int)graph[u].size() - 1, 0));
  return;
}
void bfs(int s, int t) {
  int nxt;
  queue<int> q;
  dep[s] = iter[s] = 0;
  q.push(s);
  went[s] = t;
  while (!q.empty()) {
    nxt = q.front();
    q.pop();
    for (edge i : graph[nxt])
      if (i.cap > 0 && went[i.to] != t) {
        went[i.to] = t;
        dep[i.to] = dep[nxt] + 1;
        iter[i.to] = 0;
        q.push(i.to);
      }
  }
  return;
}
int dfs(int u, int t, int nv) {
  if (u == t) return nv;
  int temp;
  for (int &i = iter[u]; i < graph[u].size(); i++) {
    edge &nxt = graph[u][i];
    if (nxt.cap > 0 && dep[nxt.to] > dep[u]) {
      temp = dfs(nxt.to, t, min(nxt.cap, nv));
      if (temp > 0) {
        nxt.cap -= temp;
        graph[nxt.to][nxt.rev].cap += temp;
        return temp;
      }
    }
  }
  return 0;
}
int dinic(int s, int t) {
  int ans = 0, cnt = 0, f;
  for (int i = 0; i < N; i++) went[i] = 0;
  while (true) {
    bfs(s, ++cnt);
    if (went[s] != went[t]) break;
    while ((f = dfs(s, t, INF)) > 0) ans += f;
  }
  return ans;
}
int id[N][N];
void solve(int n, int d) {
  int x, y, s = 0, now = 0, t = d * d + d + d + 1, ans = 0;
  vector<int> v;
  for (int i = 0; i <= t; i++) graph[i].clear();
  for (int i = 1; i <= d; i++)
    for (int j = i; j <= d; j++) {
      addedge(s, i * d + j + d, 0);
      id[i][j] = now++;
      for (int k = i; k <= j; k++) addedge(i * d + j + d, k, INF);
    }
  for (int i = 1; i <= d; i++) addedge(i, t, 0);
  if (debug) {
    for (int i = 0; i <= t; i++) {
      printf("%d::\n", i);
      for (edge j : graph[i]) printf("to=%d cap=%d\n", j.to, j.cap);
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x, &y);
    graph[s][id[x][y]].cap++;
    if (dinic(s, t) == 1)
      ;
    else {
      ans++;
      v.PB(i);
      for (int j = 1; j <= d; j++) graph[j].back().cap++;
      dinic(s, t);
    }
    if (debug) printf("ans=%d\n", ans);
    if (debug) {
      for (int i = 0; i <= t; i++) {
        printf("%d::\n", i);
        for (edge j : graph[i]) printf("to=%d cap=%d\n", j.to, j.cap);
      }
    }
  }
  printf("%d", v[0]);
  for (int i = 1; i < v.size(); i++) printf(" %d", v[i]);
  printf("\n");
  return;
}
int main() {
  int n, d;
  while (true) {
    scanf("%d", &n);
    if (n == 0) break;
    scanf("%d", &d);
    solve(n, d);
  }
}
