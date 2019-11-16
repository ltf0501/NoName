#include <bits/stdc++.h>
using namespace std;
#define maxn 505
#define pii pair<int, int>
#define F first
#define S second
vector<pii> g[maxn];
bool pos[2][maxn][maxn];
bool vis[2][maxn];
map<string, int> mp;
int main() {
  int n, m;
  cin >> n >> m;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    string s, o, t;
    cin >> s >> o >> t;
    if (mp.find(s) == mp.end()) mp[s] = ++cnt;
    if (mp.find(t) == mp.end()) mp[t] = ++cnt;
    int x = mp[s], y = mp[t];
    if (o == "is-a")
      g[x].push_back(pii(y, 1));
    else
      g[x].push_back(pii(y, 0));
  }
  for (int i = 1; i <= cnt; i++) {
    queue<pii> q;
    q.push(pii(i, 1));
    memset(vis, 0, sizeof(vis));
    while (!q.empty()) {
      pii u = q.front();
      q.pop();
      if (vis[u.S][u.F]) continue;
      vis[u.S][u.F] = 1;
      pos[u.S][i][u.F] = 1;
      for (pii v : g[u.F]) {
        q.push(pii(v.F, u.S & v.S));
      }
    }
  }
  int cas = 0;
  while (m--) {
    string s, o, t;
    cin >> s >> o >> t;
    printf("Query %d: ", ++cas);
    int x = mp[s], y = mp[t];
    if (o == "is-a") {
      puts(pos[1][x][y] ? "true" : "false");
    } else {
      puts(pos[0][x][y] ? "true" : "false");
    }
  }
  return 0;
}
