bool debug = false;
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define PB push_back
#define S second
const int N = 1e5 + 10;
int bit[N];
void add(int pos, int x) {
  pos++;
  while (pos < N) {
    bit[pos] += x;
    pos += pos & -pos;
  }
  return;
}
int ask(int pos) {
  pos++;
  int ans = 0;
  while (pos) {
    ans += bit[pos];
    pos ^= pos & -pos;
  }
  return ans;
}
int main() {
  int n, l, r, a[N], pos, left, lpos, rpos;
  long long int ans = 0;
  vector<pair<int, int>> v;
  vector<int> temp;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) v.PB({a[i], i});
  sort(v.begin(), v.end());
  for (int i = 0; i < n; i++) bit[i] = 0;
  for (int i = 0; i < n; i++) add(i, 1);
  left = n;
  for (int i = 0; i < n;) {
    if (debug) printf("now=%d", v[i].F);
    temp.clear();
    temp.PB(v[i].S);
    i++;
    while (i < n && v[i].F == v[i - 1].F) {
      temp.PB(v[i].S);
      i++;
    }
    lpos = 0;
    rpos = (int)temp.size() - 1;
    while (lpos <= rpos) {
      l = ask(temp[lpos]) - 1;
      r = left - ask(temp[rpos]);
      if (l <= r) {
        ans += l;
        add(temp[lpos], -1);
        lpos++;
      } else {
        ans += r;
        add(temp[rpos], -1);
        rpos--;
      }
      left--;
    }
  }
  printf("%lld\n", ans);
}
