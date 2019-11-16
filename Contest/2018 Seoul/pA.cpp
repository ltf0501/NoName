bool debug = false;
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 1e5 + 10;

int max(int a, int b) { return a > b ? a : b; }
struct seg_tree {
  vector<int> v, f;
  void init(int n, int l, int r) {
    if (v.size() <= n) {
      v.resize(n + 1);
      f.resize(n + 1);
    }
    if (l < r) {
      int mid = (l + r) >> 1;
      init(n * 2 + 1, l, mid);
      init(n * 2 + 2, mid + 1, r);
    }
    return;
  }
  void addtag(int n, int x) {
    v[n] += x;
    f[n] += x;
    return;
  }
  void push(int n) {
    if (f[n]) {
      addtag(n * 2 + 1, f[n]);
      addtag(n * 2 + 2, f[n]);
      f[n] = 0;
    }
    return;
  }
  void fix(int n, int l, int r, int L, int R, int x) {
    if (L <= l && r <= R)
      addtag(n, x);
    else if (!(L > r || l > R)) {
      int mid = (l + r) >> 1;
      push(n);
      fix(n * 2 + 1, l, mid, L, R, x);
      fix(n * 2 + 2, mid + 1, r, L, R, x);
      v[n] = max(v[n * 2 + 1], v[n * 2 + 2]);
    }
    return;
  }
  int ask(int n, int l, int r, int L, int R) {
    if (L <= l && r <= R)
      return v[n];
    else if (L > r || l > R)
      return 0;
    else {
      int mid = (l + r) >> 1;
      push(n);
      return max(ask(n * 2 + 1, l, mid, L, R),
                 ask(n * 2 + 2, mid + 1, r, L, R));
    }
  }
};
int main() {
  int now = 0, n, x1, x2, y1, y2, ans = 0;
  vector<int> x;
  pair<int, int> p[N];
  seg_tree sg;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x.PB(y1);
    x.PB(y2);
    p[i] = {y2, y1};
  }
  sort(x.begin(), x.end());
  x.resize(unique(x.begin(), x.end()) - x.begin());
  for (int i = 0; i < n; i++)
    p[i] = {lower_bound(x.begin(), x.end(), p[i].F) - x.begin(),
            lower_bound(x.begin(), x.end(), p[i].S) - x.begin()};
  sg.init(0, 0, (int)x.size() - 1);
  sort(p, p + n);
  for (int i = 0; i < n; i++)
    sg.fix(0, 0, (int)x.size() - 1, p[i].F, p[i].S, 1);
  for (int i = 0; i < x.size(); i++) {
    while (now < n) {
      if (p[now].F <= i) {
        pq.push({p[now].S, p[now].F});
        sg.fix(0, 0, (int)x.size() - 1, p[now].F, p[now].S, -1);
        now++;
      } else
        break;
    }
    while (!pq.empty()) {
      if (pq.top().F < i) {
        sg.fix(0, 0, (int)x.size() - 1, pq.top().S, pq.top().F, 1);
        pq.pop();
      } else
        break;
    }
    ans = max(ans, pq.size() + sg.v[0]);
    if (debug) printf("i=%d ans=%d\n", i, ans);
  }
  printf("%d\n", ans);
}
