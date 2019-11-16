#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 505
const ll INF = (ll)1e18;
ll p[maxn];
int n, m;
int main() {
  freopen("jacking.in", "r", stdin);
  int t;
  scanf("%d", &t);
  int cas = 0;
  while (t--) {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld", &p[i]);
    int q;
    scanf("%d", &q);
    printf("Case %d:\n", ++cas);
    while (q--) {
      int n, m;
      scanf("%d%d", &n, &m);
      if (n < m) {
        puts("impossible");
        continue;
      }
      ll ans = INF;
      int a = (n - m) % m;
      a = m - a;
      int x = (n - m + a) / m;
      //	printf("a=%d x=%d\n",a,x);
      ans = min(ans, 1ll * a * p[x] + 1ll * (m - a) * p[x + 1]);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
