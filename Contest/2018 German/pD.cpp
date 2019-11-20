#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const ll INF = 1e16;
int a[maxn];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int flag = 1;
  ll now = 0;
  ll le = 0, ri = INF;
  for (int i = 1; i <= n; i++) {
    now += flag * a[i];
    flag = -flag;
    if (i & 1)
      ri = min(ri, now);
    else
      le = max(le, now);
  }
  ll ans = max(0ll, ri - le + 1);
  printf("%lld\n", ans);
  return 0;
}
