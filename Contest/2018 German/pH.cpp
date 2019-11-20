#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll pw(int a, int n) {
  ll res = 1;
  for (int i = 0; i < n; i++) res *= a;
  return res;
}
int main() {
  ll m;
  scanf("%lld", &m);
  if (m == 1) {
    return puts("3 1"), 0;
  }
  for (int k = 3; k <= 60; k++) {
    ll now = 0;
    for (int i = 1;; i++) {
      now += pw(i, k - 1);
      if (now > m)
        break;
      else if (now == m) {
        return printf("%d %d\n", k, i), 0;
      }
    }
  }
  puts("impossible");
  return 0;
}
