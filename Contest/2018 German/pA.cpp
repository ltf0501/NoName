#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int kN = 1000010;

int timer, h, w;
vector<int> g[kN];
string field[kN];
int vis[1010][1010];

pair<int, int> Next(pair<int, int> p, int d) {
  const int dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
  return {p.first + dx[d], p.second + dy[d]};
}

bool CanGo(pair<int, int> p, int d) {
  auto pp = Next(p, d);
  if (pp.first < 0 || pp.first >= h || pp.second < 0 || pp.second >= w)
    return false;
  const int dx[] = {0, 1, 1, 1}, dy[] = {1, 0, 1, 2};
  return field[p.first + dx[d]][p.second * 2 + dy[d]] == ' ';
}

int dfs(pair<int, int> p) {
  int id = ++timer;
  vis[p.first][p.second] = id;
  // cerr << id << "(" << p.first << "," << p.second << ")" << '\n';
  for (int i = 0; i < 4; i++) {
    if (CanGo(p, i)) {
      auto nxt = Next(p, i);
      if (!vis[nxt.first][nxt.second]) g[id].push_back(dfs(nxt));
    }
  }
  return id;
}
int in[kN], out[kN], dfs_clock;
int dep[kN];
int anc[20][kN];

void dfs2(int u, int fa, int d) {
  in[u] = ++dfs_clock;
  anc[0][u] = fa;
  dep[u] = d;
  for (int v : g[u])
    if (v != fa) {
      dfs2(v, u, d + 1);
    }
  out[u] = dfs_clock;
}
bool ancestor(int x, int y) { return in[x] <= in[y] && out[x] >= out[y]; }
int LCA(int x, int y) {
  if (ancestor(x, y)) return x;
  if (ancestor(y, x)) return y;
  for (int i = 19; i >= 0; i--)
    if (!ancestor(anc[i][x], y)) x = anc[i][x];
  return anc[0][x];
}
int dis(int x, int y) { return dep[x] + dep[y] - 2 * dep[LCA(x, y)]; }
int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  cin >> h >> w >> ws;
  for (int i = 0; i <= h; i++) getline(cin, field[i]);
  int root = dfs({0, 0});
  int n;
  cin >> n;
  vector<int> v;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    v.push_back(vis[x][y]);
  }
  dfs2(1, 0, 0);
  out[0] = dfs_clock;
  for (int j = 1; j <= 19; j++)
    for (int i = 1; i <= h * w; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]];
  ll ans = 0;
  //	printf("v: ");
  //	for(int x : v) printf("%d ", x); puts("");
  for (int i = 1; i < int(v.size()); i++) {
    ans += dis(v[i - 1], v[i]);
  }
  printf("%lld\n", ans);
  return 0;
}
