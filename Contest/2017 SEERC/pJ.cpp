#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int one, n_one, two;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    if (x == 1)
      one++;
    else
      n_one++;
    if (x == 2) two++;
  }
  bool flag = 1;
  if (n_one == 0) {
    if (one % 3 == 0) flag = 0;
  } else if (n_one == 1) {
    flag = 1;
  } else if (n_one == 2) {
    if (one % 3 == 0 || two == 0) flag = 0;
  } else
    flag = 0;
  puts(flag ? "Win" : "Lose");
  return 0;
}
