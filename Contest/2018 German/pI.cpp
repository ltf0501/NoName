#include <stdio.h>
const int N = 1e3 + 10;
int n, a[N], b[N];
bool ok() {
  for (int i = 1; i <= n; i++)
    if (a[i] > b[i])
      return true;
    else if (b[i] > a[i])
      return false;
  return true;
}
int main() {
  int ans;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
  if (b[1] < a[1])
    printf("0\n");
  else {
    ans = b[1] - a[1];
    for (int i = 1; i <= n; i++) a[i] += ans;
    if (ok())
      printf("%d\n", ans);
    else
      printf("%d\n", ans + 1);
  }
}
