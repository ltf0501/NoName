#include <stdio.h>
long long int gcd(long long int a, long long int b) {
  return b == 0 ? a : gcd(b, a % b);
}
int main() {
  long long int temp, l, w, r;
  bool ans = false;
  scanf("%lld%lld%lld", &l, &r, &w);
  if (r + w <= l) {
    printf("OK\n");
    return 0;
  }
  temp = gcd(w, r);
  if (l - w < r - temp)
    ans = true;
  else
    ans = false;
  if (!ans)
    printf("OK\n");
  else
    printf("DEADLOCK\n");
}
