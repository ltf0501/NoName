#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
#define SZ(v) ((int)v.size())
const double INF = 1e9;
struct P {
  double x, y;
  P() {}
  P(double _x, double _y) { x = _x, y = _y; }
  bool operator<(const P& rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
  P operator+(const P& rhs) const { return P(x + rhs.x, y + rhs.y); }
  P operator-(const P& rhs) const { return P(x - rhs.x, y - rhs.y); }
  double operator*(const P& rhs) const { return x * rhs.x + y * rhs.y; }
  P operator+(double a) const { return P(a * x, a * y); }
  double operator^(const P& rhs) const { return x * rhs.y - y * rhs.x; }
  bool operator==(const P& rhs) { return x == rhs.x && y == rhs.y; }
};
int fa[maxn];
bool inhull[maxn];
vector<P> ss[maxn];
inline double dis(P a, P b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
vector<P> A;
P now;
bool cmp(P x, P y) {
  double cal = (x - now) ^ (y - now);
  if (cal != 0) return cal > 0;
  return dis(x, now) < dis(y, now);
}
vector<P> ConvexHull(vector<P> p) {
  vector<P> res;
  vector<int> id;
  res.push_back(p[0]);
  id.push_back(0);
  for (int i = 1; i < SZ(p); i++) {
    while (SZ(res) >= 2) {
      if (((p[i] - res[SZ(res) - 2]) ^ (res[SZ(res) - 1] - res[SZ(res) - 2])) >=
          0)
        res.pop_back(), id.pop_back();
      else
        break;
    }
    res.push_back(p[i]), id.push_back(i);
  }
  for (int i : id) inhull[i] = 1;
  return res;
}
/*
vector<P> ConvexHull(vector<P> p)
{
    vector<P> res;
    for(int i=0;i<SZ(p);i++)
    {
        while(SZ(res)>=2)
        {
            if((p[i]-res[SZ(res)-2])^(res[SZ(res)-1]-res[SZ(res)-2])>=0)res.pop_back();
            else break;
        }
    }
    vector<P> tmp;
    for(int i=SZ(p)-1;i>=0;i--)
    {
        while(SZ(tmp)>=2)
        {
            if((p[i]-tmp[SZ(tmp)-2])^(tmp[SZ(tmp)-1]-tmp[SZ(tmp)-2])>=0)tmp.pop_back();
            else break;
        }
    }
    for(int i=1;i<SZ(tmp)-1;i++)res.push_back(tmp[i]);
    return res;
}
*/
bool inpoly(P a, vector<P> p) {
  double pre = 0;
  int m = SZ(p);
  for (int i = 0; i < m; i++) {
    double cur = (a - p[i]) ^ (a - p[(i + 1) % m]);
    if (i > 0 && pre * cur <= 0) return 0;
    pre = cur;
  }
  return 1;
}
int main() {
  int n;
  scanf("%d", &n);
  A.resize(n);
  for (int i = 0; i < n; i++) scanf("%lf %lf", &A[i].x, &A[i].y);
  int id = 0;
  for (int i = 1; i < n; i++) {
    if (A[i] < A[id]) id = i;
  }
  if (id != 0) swap(A[0], A[id]);
  now = A[0];
  sort(A.begin() + 1, A.end(), cmp);
  for (int i = 0; i < n; i++) printf("%d: %.0f %.0f\n", i, A[i].x, A[i].y);
  puts("ConvexHull: ");
  vector<P> convex = ConvexHull(A);
  int m = SZ(convex);
  for (int i = 0; i < m; i++) printf("%.0f %.0f\n", convex[i].x, convex[i].y);
  double tot = 0.0;
  for (int i = 0; i < m; i++) tot += dis(convex[i], convex[(i + 1) % m]);
  printf("tot = %.3f\n", tot);

  for (int i = 0; i < n; i++) printf("inhull[%d] = %d\n", i, inhull[i]);
  ss[1].push_back(A[0]);
  for (int i = 1, cur = 0; i < n; i++) {
    if (inhull[i]) {
      cur++;
      if (cur != 1) ss[(cur - 1 + m) % m].push_back(A[i]);
      if (cur != m - 1) ss[(cur + 1) % m].push_back(A[i]);
    } else {
      vector<P> tmp;
      if (cur > 0) {
        tmp.push_back(convex[(cur - 1 + m) % m]), tmp.push_back(convex[cur]),
            tmp.push_back(convex[(cur + 1) % m]);
        if (inpoly(A[i], tmp)) ss[cur].push_back(A[i]);
      }
      tmp.clear();
      if (cur != m - 1) {
        tmp.push_back(convex[cur]), tmp.push_back(convex[(cur + 1) % m]),
            tmp.push_back(convex[(cur + 2) % m]);
        if (inpoly(A[i], tmp)) ss[(cur + 1) % m].push_back(A[i]);
      }
    }
  }
  ss[m - 1].push_back(A[0]);
  vector<P> tmp;
  tmp.push_back(convex[m - 1]), tmp.push_back(convex[0]),
      tmp.push_back(convex[1]);
  ss[0].push_back(convex[m - 1]);
  for (int i = n - 1; i >= 1; i--) {
    if (!inhull[i] && inpoly(A[i], tmp)) ss[0].push_back(A[i]);
  }
  ss[0].push_back(convex[1]);
  for (int i = 0; i < m; i++) {
    printf("i = %d:\n", i);
    for (P point : ss[i]) printf("%0.f %.0f\n", point.x, point.y);
  }

  double ans1 = 0;
  for (int i = 0; i < m; i++) {
    P a = convex[(i - 1 + m) % m], b = convex[i], c = convex[(i + 1) % m],
      d = convex[(i + 2) % m];
    ans1 = max(ans1, dis(a, b) + dis(b, c) + dis(c, d) - dis(a, d));
  }
  printf("ans1 = %.3f\n", ans1);
  double pre_max = 0, umr = 0, ans2 = 0;
  for (int i = 2; i < m - 1; i++) {
    P a1 = convex[(i - 3 + m) % m], b1 = convex[(i - 2 + m) % m],
      c1 = convex[(i - 1 + m) % m];
    P a2 = convex[(i - 1 + m) % m], b2 = convex[i], c2 = convex[(i + 1) % m];
    pre_max = max(pre_max, dis(a1, b1) + dis(b1, c1) - dis(a1, c1));
    ans2 = max(ans2, pre_max + (dis(a2, b2) + dis(b2, c2) - dis(a2, c2)));
  }
  // i=m-1
  P a = convex[m - 2], b = convex[m - 1], c = convex[0];
  umr = dis(a, b) + dis(b, c) - dis(a, c);
  for (int i = 1; i < m - 2; i++) {
    P a1 = convex[(i - 1 + m) % m], b1 = convex[i], c1 = convex[(i + 1) % m];
    ans2 = min(ans2, umr + (dis(a1, b1) + dis(b1, c1) - dis(a1, c1)));
  }
  printf("ans2 = %.3f\n", ans2);
  double ans3 = 0;
  for (int i = 0; i < m; i++) {
    now = convex[(i - 1 + m) % m];
    int id = 0;
    for (int j = 0; j < SZ(ss[i]); j++) {
      if (ss[i][j] == now) {
        id = j;
        break;
      }
    }
    if (id != 0) swap(ss[i][0], ss[i][id]);
    sort(ss[i].begin() + 1, ss[i].end(), cmp);
    printf("i = %d\n", i);
    vector<P> con = ConvexHull(ss[i]);
    double sum = 0;
    for (int j = 0; j < SZ(con) - 1; j++) sum += dis(con[j], con[j + 1]);
    double sub = 0;
    for (int j = 1; j < SZ(con) - 1; j++)
      sub = max(sub, dis(con[j - 1], con[j]) + dis(con[j], con[j + 1]) -
                         dis(con[j - 1], con[j + 1]));
    sum -= sub;
    ans3 = max(ans3, (dis(convex[(i - 1 + m) % m], convex[i]) +
                      dis(convex[i], convex[(i + 1) % m])) -
                         sum);
  }
  printf("ans3 = %.3f\n", ans3);
  double ans = max({ans1, ans2, ans3});
  printf("%.9f\n", ans);
  return 0;
}
