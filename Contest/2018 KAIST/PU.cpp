#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct Point {
  ll x, y;
  Point() {}
  Point(ll _x, ll _y) { x = _x, y = _y; }
  bool operator<(const Point& rhs) const {
    return x != rhs.x ? x < rhs.x : y < rhs.y;
  }
  Point operator+(const Point& rhs) const {
    return Point(x + rhs.x, y + rhs.y);
  }
  Point operator-(const Point& rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
  ll operator*(const Point& rhs) const { return x * rhs.x + y * rhs.y; }
  ll operator^(const Point& rhs) const { return x * rhs.y - y * rhs.x; }
};
ll dis(Point a, Point b) { return (a - b) * (a - b); }
struct Geometry {
  vector<Point> v;
  vector<int> convex;
  void init() {
    v.clear();
    convex.clear();
  }
  void add_point(int a, int b) { v.push_back(Point(a, b)); }
  void Convex_Hull(int& r) {
    // sort(v.begin(),v.end());
    vector<int> tmp;
    for (int i = 0; i < (int)v.size(); i++) {
      int SZ;
      while ((SZ = (int)tmp.size()) >= 2 &&
             ((v[tmp[SZ - 1]] - v[tmp[SZ - 2]]) ^ (v[i] - v[tmp[SZ - 2]])) <= 0)
        tmp.pop_back();
      tmp.push_back(i);
    }
    r = (int)tmp.size() - 1;
    for (int i : tmp) convex.push_back(i);
    tmp.clear();
    for (int i = (int)v.size() - 1; i >= 0; i--) {
      int SZ;
      while ((SZ = (int)tmp.size()) >= 2 &&
             ((v[tmp[SZ - 1]] - v[tmp[SZ - 2]]) ^ (v[i] - v[tmp[SZ - 2]])) <= 0)
        tmp.pop_back();
      tmp.push_back(i);
    }
    for (int i = 1; i < (int)tmp.size(); i++) convex.push_back(tmp[i]);
  }
  ll cal() {
    if (v.size() == 1) return 0;
    if (v.size() == 2) return dis(v[0], v[1]);
    int r;
    Convex_Hull(r);
    //		for(int i : convex)printf("%d: %lld %lld\n",i,v[i].x,v[i].y);
    ll ans = 0;
    for (int i = 0, j = r; i < r && r < (int)convex.size() - 1; i++) {
      //			printf("%d %d:
      //%lld\n",convex[i],convex[j],dis(v[convex[i]],v[convex[j]]));
      ans = max(ans, dis(v[convex[i]], v[convex[j]]));
      while (((v[convex[i + 1]] - v[convex[i]]) ^
              (v[convex[j + 1]] - v[convex[j]])) > 0)
        j++, ans = max(ans, dis(v[convex[i]], v[convex[j]]));
      //				printf("%d %d:
      //%lld\n",convex[i],convex[j],dis(v[convex[i]],v[convex[j]]));
    }
    return ans;
  }
};
#define maxn 250010
#define pii pair<ll, ll>
#define F first
#define S second
int n, k;
pii a[maxn];
Geometry solver;
bool check(ll mid) {
  for (int i = 1, tot = 0; i <= n; i++) {
    if (tot == k) return 0;
    tot++;
    int j;
    int l = i;
    while (l < n && a[l + 1].F == a[i].F) l++;
    solver.init();
    for (int t = i; t <= l; t++) solver.add_point(a[t].F, a[t].S);
    if (solver.cal() > mid) return 0;
    for (j = 1;; j++) {
      int r = l + (1 << j) - 1;
      solver.init();
      for (int t = i; t <= min(n, r); t++) solver.add_point(a[t].F, a[t].S);
      ll s = solver.cal();
      //	printf("%d %d: %lld\n",i,min(n,r),s);
      if (s > mid) break;
      if (r >= n) return 1;
    }
    j--;
    int le = i + (1 << j) - 1, ri = min(n, i + (1 << (j + 1)) - 1);
    int res = le;
    while (le <= ri) {
      solver.init();
      int m = (le + ri) >> 1;
      //			printf("now = %d\n",m);
      for (int t = i; t <= m; t++) solver.add_point(a[t].F, a[t].S);
      ll s = solver.cal();
      //	printf("XD %d %d %lld\n",i,m,s);
      if (s <= mid)
        res = m, le = m + 1;
      else
        ri = m - 1;
    }
    if (res < n && a[res].F == a[res + 1].F) res--;
    //	printf("pos: %d %d\n",i,res);
    i = res;
  }
  return 1;
}
int main() {
  //	Geometry solver;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%lld%lld", &a[i].F, &a[i].S);
  sort(a + 1, a + n + 1);
  int p = 0;
  for (int i = 1, r = 1; i <= n; i = r) {
    while (r <= n && a[r].F == a[i].F) r++;
    a[++p] = a[i];
    if (r - 1 != i) a[++p] = a[r - 1];
  }
  n = p;
  // printf("n = %d\n",n);
  // for(int i=1;i<=n;i++)printf("%d %d\n",a[i].F,a[i].S);
  // puts("");
  // for(int i=1;i<=n;i++)solver.add_point(a[i].F,a[i].S);
  //	printf("%lld\n",solver.cal());
  ll l = 0, r = 2000000000000000005ll;
  ll ans = r;
  while (l <= r) {
    ll mid = (l + r) >> 1;
    //	printf("cur = %lld\n",mid);
    if (check(mid))
      ans = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  printf("%lld\n", ans);
  return 0;
}
