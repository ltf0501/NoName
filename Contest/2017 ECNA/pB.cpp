#include <bits/stdc++.h>
using namespace std;
#define maxn 2000010
const double pi = acos(-1);
struct P {
  double x, y;
  P(double xx = 0, double yy = 0) { x = xx, y = yy; }
};
bool operator<(const P& a, const P& b) {
  return a.x != b.x ? a.x < b.x : a.y < b.y;
}
P operator+(const P& a, const P& b) { return P(a.x + b.x, a.y + b.y); }
P operator-(const P& a, const P& b) { return P(a.x - b.x, a.y - b.y); }
double operator^(const P& a, const P& b) { return a.x * b.y - a.y * b.x; }
double dis(P a, P b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
P a[maxn];
vector<P> v, ans;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int x, y, r;
    scanf("%d%d%d", &x, &y, &r);
    r += 10;
    for (int j = 0; j < 10000; j++)
      a[i * 10000 + j] =
          P(x + cos(j * 2 * pi / 10000) * r, y + sin(j * 2 * pi / 10000) * r);
  }
  sort(a, a + 10000 * n);
  n *= 10000;
  for (int i = 0; i < n; i++) {
    while ((int)v.size() >= 2) {
      int now = (int)v.size() - 1;
      if ((v[now] - v[now - 1] ^ (a[i] - v[now - 1])) <= 0)
        v.pop_back();
      else
        break;
    }
    v.push_back(a[i]);
  }
  for (P t : v) ans.push_back(t);
  v.clear();
  for (int i = n - 1; i >= 0; i--) {
    while ((int)v.size() >= 2) {
      int now = (int)v.size() - 1;
      if ((v[now] - v[now - 1] ^ (a[i] - v[now - 1])) <= 0)
        v.pop_back();
      else
        break;
    }
    v.push_back(a[i]);
  }
  for (int i = 1; i < (int)v.size(); i++) ans.push_back(v[i]);
  double sum = 0;
  for (int i = 0; i < (int)ans.size() - 1; i++) sum += dis(ans[i], ans[i + 1]);
  printf("%10f\n", sum);
  return 0;
}
