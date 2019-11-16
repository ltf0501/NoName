#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
vector<int> p;
int p_fac[maxn];
int psz;
void pre() {
  for (int i = 2; i < maxn; i++) {
    if (!p_fac[i]) p.push_back(i), p_fac[i] = i;
    for (int j = 0; j < int(p.size()) && 1LL * i * p[j] < maxn; j++) {
      p_fac[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
  //	for(int i = 2; i <= 30; i++)
  //		printf("%d: %d\n", i, p_fac[i]);
}
int a[maxn];
vector<int> pos[maxn];
int main() {
  pre();
  psz = int(p.size());
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < int(p.size()); i++) pos[p[i]].push_back(0);
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    while (x > 1) {
      int pp = p_fac[x];
      pos[pp].push_back(i);
      while (x % pp == 0) x /= pp;
    }
  }
  for (int i = 0; i < int(p.size()); i++) pos[p[i]].push_back(n + 1);
  //	for(int i = 2; i < 30; i++) if(p_fac[i] == i) {
  //		printf("%d: ", i);
  //		for(int j : pos[i]) printf("%d ", j); puts("");
  //	}
  //	printf("psz = %d\n", psz);
  ll ans = 1LL * n * (n + 1) / 2 * psz;
  //	printf("%lld\n", ans);
  for (int i = 0; i < psz; i++) {
    ll tmp = 0;
    for (int j = 0; j < int(pos[p[i]].size()) - 1; j++) {
      int l = pos[p[i]][j], r = pos[p[i]][j + 1];
      int x = r - l - 1;
      tmp += 1LL * x * (x + 1) / 2;
    }
    ans -= tmp;
  }
  printf("%lld\n", ans);
  return 0;
}
