bool debug = false;
#include <stdio.h>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define PB push_back
#define F first
#define S second
struct value {
  long long int ans, step, nxt;
};
map<long long int, value> m;
long long int ABS(long long int n) { return n >= 0 ? n : -n; }
value go(long long int n) {
  if (m.find(n) != m.end()) return m[n];
  long long int tmp, now = 10;
  value ans = {n, 0, n}, tp;
  while (now <= n) {
    tmp = ABS((n / now) - (n % now));
    if (tmp != 0) {
      tp = go(tmp);
      if (tp.ans < ans.ans) {
        ans = {tp.ans, tp.step, tmp};
      }
    }
    now *= 10;
  }
  ans.step += 1;
  m.insert({n, ans});
  return ans;
}
void solve() {
  long long int n;
  value tmp;
  scanf("%lld", &n);
  tmp = go(n);
  printf("%lld %lld", tmp.step, n);
  while (tmp.nxt != tmp.ans) {
    printf(" %lld", tmp.nxt);
    tmp = m[tmp.nxt];
  }
  if (n != tmp.ans)
    printf(" %lld\n", tmp.ans);
  else
    printf("\n");
  return;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) solve();
}
