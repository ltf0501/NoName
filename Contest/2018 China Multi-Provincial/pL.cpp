bool debug = false;
#include <stdio.h>
#include <map>
#include <stack>
#include <utility>
using namespace std;
#define F first
#define S second
constexpr int kN = int(1E5 + 10);
struct seg_tree {
  int a[kN << 2], cnt[kN << 2], flag[kN << 2];
  void pull(int n) {
    if (a[n * 2 + 1] == a[n * 2 + 2]) {
      cnt[n] = cnt[n * 2 + 1] + cnt[n * 2 + 2];
      a[n] = a[n * 2 + 1];
    } else if (a[n * 2 + 1] > a[n * 2 + 2]) {
      cnt[n] = cnt[n * 2 + 2];
      a[n] = a[n * 2 + 2];
    } else {
      cnt[n] = cnt[n * 2 + 1];
      a[n] = a[n * 2 + 1];
    }
    return;
  }
  void push(int n) {
    if (flag[n]) {
      a[n * 2 + 1] += flag[n];
      a[n * 2 + 2] += flag[n];
      flag[n * 2 + 1] += flag[n];
      flag[n * 2 + 2] += flag[n];
      flag[n] = 0;
    }
    return;
  }
  void init(int n, int l, int r) {
    flag[n] = 0;
    if (l == r) {
      a[n] = 1;
      cnt[n] = 1;
    } else {
      int mid = (l + r) >> 1;
      init(n * 2 + 1, l, mid);
      init(n * 2 + 2, mid + 1, r);
      pull(n);
    }
    return;
  }
  void fix(int n, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R) {
      a[n] += x;
      flag[n] += x;
    } else if (!(L > r || l > R)) {
      push(n);
      int mid = (l + r) >> 1;
      fix(n * 2 + 1, l, mid, L, R, x);
      fix(n * 2 + 2, mid + 1, r, L, R, x);
      pull(n);
    }
    return;
  }
};
int a[kN];
seg_tree sg;
void solve() {
  int n, lst;
  long long int ans = 0;
  map<int, int> mp;
  stack<pair<int, int>> tp, lw;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  sg.init(0, 1, n);
  for (int i = n; i >= 1; i--) {
    lst = i;
    while (!tp.empty()) {
      if (tp.top().F < a[i]) {
        sg.fix(0, 1, n, lst + 1, tp.top().S, a[i] - tp.top().F);
        if (debug)
          printf("fix(%d, %d, %d)\n", lst + 1, tp.top().S, a[i] - tp.top().F);
        lst = tp.top().S;
        tp.pop();
      } else
        break;
    }
    tp.push({a[i], lst});
    lst = i;
    while (!lw.empty()) {
      if (lw.top().F > a[i]) {
        sg.fix(0, 1, n, lst + 1, lw.top().S, lw.top().F - a[i]);
        if (debug)
          printf("fix(%d, %d, %d)\n", lst + 1, lw.top().S, lw.top().F - a[i]);
        lst = lw.top().S;
        lw.pop();
      } else
        break;
    }
    lw.push({a[i], lst});
    if (mp.find(a[i]) == mp.end()) mp.insert({a[i], n + 1});
    if (debug) printf("fix(%d, %d, %d)\n", i, mp[a[i]] - 1, -1);
    sg.fix(0, 1, n, i, mp[a[i]] - 1, -1);
    mp[a[i]] = i;
    if (sg.a[0] == 0) ans += sg.cnt[0];
  }
  printf("%lld\n", ans);
}
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }
}
