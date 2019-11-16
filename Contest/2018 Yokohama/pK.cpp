bool debug = false;
#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
void swap(int &a, int &b) {
  a ^= b;
  b ^= a;
  a ^= b;
  return;
}
vector<int> a, v, m;
int n;
bool can(int pos, int need) {
  if (need <= 0) return true;
  vector<int> temp, r;
  for (int i : v)
    if (i >= 0) temp.PB(i);
  for (int i : m)
    if (i >= 0) r.PB(i);
  if (debug) {
    printf("pos=%d need=%d\n", pos, need);
    printf("temp::");
    for (int i : temp) printf(" %d", i);
    printf("\nr::");
    for (int i : r) printf(" %d", i);
    printf("\n");
  }
  for (int i = 0; i < need; i++)
    if (temp[n - pos - need + i] <= r[i]) return false;
  return true;
}
int main() {
  scanf("%d", &n);
  int temp, al, apos, ar, l, r, pos, mid, win = 0, alr = 0;
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    scanf("%d", &temp);
    a.PB(temp);
    m.PB(temp);
  }
  sort(m.begin(), m.end());
  for (int i = 0; i < n; i++) {
    scanf("%d", &temp);
    v.PB(temp);
  }
  sort(v.begin(), v.end());
  for (int i = n; i >= 0; i--)
    if (can(0, i)) {
      win = i;
      break;
    }
  if (debug) printf("win=%d\n", win);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      if (m[j] == a[i]) {
        m[j] = -1;
        break;
      }
    if (v[0] > a[i]) {
      if (debug) printf("all big\n");
      l = 0;
      r = (int)v.size();
      while (r - l > 1) {
        if (debug) printf("l=%d r=%d\n", l, r);
        mid = (l + r) >> 1;
        temp = v[mid];
        v[mid] = -1;
        if (can(i + 1, win - alr - 1))
          l = mid;
        else
          r = mid;
        v[mid] = temp;
      }
    } else if (v.back() <= a[i]) {
      if (debug) printf("all small\n");
      l = 0;
      r = (int)v.size();
      while (r - l > 1) {
        if (debug) printf("l=%d r=%d\n", l, r);
        mid = (l + r) >> 1;
        temp = v[mid];
        v[mid] = -1;
        if (can(i + 1, win - alr))
          l = mid;
        else
          r = mid;
        v[mid] = temp;
      }
    } else {
      al = 0;
      ar = (int)v.size() - 1;
      while (ar - al > 1) {
        mid = (al + ar) >> 1;
        if (v[mid] > a[i])
          ar = mid;
        else
          al = mid;
      }
      l = ar;
      r = (int)v.size();
      temp = v[l];
      v[l] = -1;
      if (can(i + 1, win - alr - 1)) {
        v[l] = temp;
        if (debug) printf("big good\n");
        while (r - l > 1) {
          if (debug) printf("l=%d r=%d\n", l, r);
          mid = (l + r) >> 1;
          temp = v[mid];
          v[mid] = -1;
          if (can(i + 1, win - alr - 1))
            l = mid;
          else
            r = mid;
          v[mid] = temp;
        }
      } else {
        if (debug) printf("small good\n");
        v[l] = temp;
        l = 0;
        r = al + 1;
        while (r - l > 1) {
          if (debug) printf("l=%d r=%d\n", l, r);
          mid = (l + r) >> 1;
          temp = v[mid];
          v[mid] = -1;
          if (can(i + 1, win - alr))
            l = mid;
          else
            r = mid;
          v[mid] = temp;
        }
      }
    }
    pos = l;
    if (debug) printf("i=%d pos=%d\n", i, pos);
    if (v[pos] > a[i]) alr++;
    ans.PB(v[pos]);
    for (int j = pos + 1; j < v.size(); j++) swap(v[j], v[j - 1]);
    v.pop_back();
    if (debug) printf("done\n");
  }
  printf("%d", ans[0]);
  for (int i = 1; i < n; i++) printf(" %d", ans[i]);
  printf("\n");
}
