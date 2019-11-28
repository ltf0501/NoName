#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  int cas = 0;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("Case #%d: ", ++cas);
    if (n == 1) {
      printf("1.000000 ");
    } else
      printf("0.500000 ");
    printf("%.6f\n", double(m + 1) / double(2 * m));
  }
  return 0;
}
