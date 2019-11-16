#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
#define PB push_back
const int N = 1e3 + 10;
const int INF = 1e9 + 10;
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
void solve(int x, int y, int m) {
  int l, r, s = x + y, t = x + y + 1;
  for (int i = 0; i <= t; i++) graph[i].clear();
  for (int i = 0; i < x; i++) addedge(s, i, 1);
  for (int i = 0; i < y; i++) addedge(i + x, t, 1);
  while (m--) {
    scanf("%d%d", &l, &r);
    addedge(l, r + x, 1);
  }
  printf("%d\n", dinic(s, t));
}
int main() {
  int m, n, e;
  while (true) {
    scanf("%d", &m);
    if (m == 0) break;
    scanf("%d%d", &n, &e);
    solve(m, n, e);
  }
}
