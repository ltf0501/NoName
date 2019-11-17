#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

constexpr int kN = 2E5 + 10;
constexpr double kEps = 1E-8;

struct P {
  int64_t x, y;
  P(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}
  P operator-(P b) const { return P(x - b.x, y - b.y); }
  int64_t operator^(P b) const { return x * b.y - y * b.x; }
  bool operator<(P b) const { return x != b.x ? x < b.x : y < b.y; }
  long double abs() const { return hypot<long double>(x, y); }
};

vector<P> ConvexHull(vector<P> &ps) {
  vector<P> p;
  for (int i = 0; i < int(ps.size()); i++) {
    while (p.size() >= 2 && ((ps[i] - p[p.size() - 2]) ^
                             (p[p.size() - 1] - p[p.size() - 2])) >= 0)
      p.pop_back();
    p.push_back(ps[i]);
  }
  int t = int(p.size());
  for (int i = int(ps.size()) - 2; i >= 0; i--) {
    while (int(p.size()) > t && ((ps[i] - p[p.size() - 2]) ^
                                 (p[p.size() - 1] - p[p.size() - 2])) >= 0)
      p.pop_back();
    p.push_back(ps[i]);
  }
  p.pop_back();
  return p;
}

long double DistToLine(P a, P b, P o) {
  return abs(((a - o) ^ (b - o)) / (a - b).abs());
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  int r;
  cin >> r;
  vector<P> ps(n);
  for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
  sort(ps.begin(), ps.end());
  auto p = ConvexHull(ps);
  n = int(p.size());
  cerr << "---\n";
  cerr << n << '\n';
  for (auto ppp : p) cerr << ppp.x << ' ' << ppp.y << '\n';
  cerr << "---\n";
  long double ans = r * 2;
  for (int i = 0, j = 1; i < n; i++) {
    while (DistToLine(p[i], p[(i + 1) % n], p[(j + 1) % n]) -
               DistToLine(p[i], p[(i + 1) % n], p[j]) >
           0)
      j = (j + 1) % n;
    cerr << DistToLine(p[i], p[(i + 1) % n], p[j]) << '\n';
    long double tmp = 0;
    for (int jj = j - 10; jj <= j + 10; jj++) {
      tmp = max(tmp, DistToLine(p[i], p[(i + 1) % n], p[(jj % n + n) % n]));
    }
    ans = min(ans, tmp);
  }
  cout << fixed << setprecision(20) << ans << '\n';
}
