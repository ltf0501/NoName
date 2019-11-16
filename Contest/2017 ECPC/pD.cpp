#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define ll long long
vector<int> v[maxn], num[maxn], c;
int n;
int p[maxn], sz[maxn];
int finds(int x) { return p[x] == x ? x : p[x] = finds(p[x]); }
bool vis[maxn];
int main() {
  freopen("dream.in", "r", stdin);
  int t;
  scanf("%d", &t);
  int cas = 0;
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i < maxn; i++) v[i].clear(), num[i].clear();
    for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    for (int i = 1; i <= n; i++) {
      int x;
      scanf("%d", &x);
      v[x].push_back(i);
    }
    for (int i = 1; i < maxn; i++)
      for (int j = i; j < maxn; j += i) {
        for (int id : v[j]) num[i].push_back(id);
      }
    int cnt = 0;
    ll ans = 0;
    for (int i = maxn - 1; i >= 1; i--) {
      if (num[i].empty()) continue;
      int tmp = 0;
      for (int id : num[i])
        if (!vis[finds(id)]) vis[finds(id)] = 1, tmp++, c.push_back(finds(id));
      for (int j = 1; j < (int)num[i].size(); j++)
        p[finds(num[i][j])] = finds(num[i][0]);
      for (int x : c) vis[x] = 0;
      c.clear();
      cnt += tmp - 1;
      ans += 1ll * (tmp - 1) * i;
      if (cnt == n - 1) break;
    }
    printf("Case %d: %lld\n", ++cas, ans);
  }
  return 0;
}
