bool debug = false;
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 1e5 + 10;
int main() {
  vector<int> v;
  long long int n, tt = 0, m, sb[N], a[N], b[N], nt = 0, to = 1, now = 1,
                   tot = 0;
  priority_queue<pair<int, int>> pq;
  scanf("%lld%lld", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
  sb[0] = 0;
  for (int i = 1; i <= n; i++) sb[i] = sb[i - 1] + b[i];
  while (to <= n) {
    if (tot + a[to] <= m) {
      tot += a[to];
      to++;
    } else
      break;
  }
  if (debug) printf("tot=%d to=%d\n", tot, to);
  to--;
  if (to == 0) {
    printf("-1\n");
    return 0;
  }
  for (int i = 1; i <= to; i++) pq.push({b[i], i});
  for (int i = 1; i <= to; i++) {
    tt += a[i];
    if (debug) printf("i=%d tt=%lld\n", i, tt);
    while (now <= to && sb[now] + nt < tt) now++;
    if (debug) printf("now=%lld\n", now);
    while (!pq.empty()) {
      if (pq.top().S < now)
        pq.pop();
      else
        break;
    }
    if (pq.empty()) {
      printf("-1\n");
      return 0;
    }
    if (debug) printf("pq.top()=(%d,%d)\n", pq.top().F, pq.top().S);
    if (sb[pq.top().S] + nt <= m) v.PB(sb[pq.top().S] + nt);
    nt += pq.top().F;
  }
  if (now == to && nt + sb[to] <= m) {
    printf("-1\n");
    return 0;
  }
  printf("%d\n", (int)v.size());
  if (!v.empty()) printf("%d", v[0]);
  for (int i = 1; i < v.size(); i++) printf(" %d", v[i]);
  printf("\n");
}
