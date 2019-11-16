#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
vector<pair<int, int>> v;
bool ok(int val) {
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  int now, cnt = 0, last, nc, np;
  pair<int, int> nxt;
  for (int i = 0; i < v.size(); i++) {
    now = v[i].F;
    while (!pq.empty()) {
      last = pq.top().F;
      nc = cnt;
      np = (int)pq.size();
      if (last > now) break;
      while (!pq.empty()) {
        if (pq.top().F == last) {
          nxt = pq.top();
          pq.pop();
          cnt++;
          if (nc - nxt.S + np > val) return false;
        } else
          break;
      }
    }
    pq.push({v[i].S, cnt});
    while (i + 1 < v.size()) {
      if (v[i + 1].F <= now) {
        i++;
        pq.push({v[i].S, cnt});
      } else
        break;
    }
  }
  while (!pq.empty()) {
    last = pq.top().F;
    nc = cnt;
    np = (int)pq.size();
    while (!pq.empty()) {
      if (pq.top().F == last) {
        nxt = pq.top();
        pq.pop();
        cnt++;
        if (nc - nxt.S + np > val) return false;
      } else
        break;
    }
  }
  return true;
}
int fmax() {
  int l = 0, r = (int)v.size(), mid;
  sort(v.begin(), v.end());
  while (r - l > 1) {
    mid = (l + r) >> 1;
    if (ok(mid))
      r = mid;
    else
      l = mid;
  }
  return r;
}
int fmin() {
  priority_queue<int, vector<int>, greater<int>> pq;
  sort(v.begin(), v.end());
  pq.push(0);
  for (pair<int, int> i : v) {
    if (i.F < pq.top())
      pq.push(i.S);
    else {
      pq.pop();
      pq.push(i.S);
    }
  }
  return (int)pq.size();
}
int main() {
  int n, l, r;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &l, &r);
    v.PB({l, r});
  }
  printf("%d %d\n", fmax(), fmin());
}
