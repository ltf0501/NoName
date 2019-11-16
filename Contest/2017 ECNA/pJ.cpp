#include <stdio.h>
long long int max(long long int a, long long int b) { return a > b ? a : b; }
int main() {
  long long int u[30], r[30], up[30], rp[30], tp[30], temp, now = 0;
  for (int i = 0; i < 10; i++) scanf("%lld%lld", &u[i], &r[i]);
  for (int i = 0; i < 10; i++) scanf("%lld%lld%lld", &up[i], &rp[i], &tp[i]);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      temp = (now - tp[j]) % (up[j] + rp[j]);
      if (temp < 0) temp += up[j] + rp[j];
      if (temp < up[j] && now >= tp[j]) {
        now += up[j] - temp;
        temp = up[j];
      }
      now += u[j] + r[j];
      temp += u[j];
      if (temp >= up[j] + rp[j]) tp[j] = max(tp[j], now - r[j]);
      //	printf("i=%lld j=%lld now=%lld\n",i,j,now);
    }
  }
  printf("%lld\n", now - r[9]);
}
