// WA
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
constexpr double kEps = 1E-10;
const double kPi = acos(-1);
const int kN = 1e5 + 10;
const int kInf = 1e9;
int dcmp(double x) {
  if (fabs(x) < kEps) return 0;
  return x < 0 ? -1 : 1;
}
bool same(double a, double b) { return dcmp(a - b) == 0; }
struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator+(P b) const { return P(x + b.x, y + b.y); }
  P operator-(P b) const { return P(x - b.x, y - b.y); }
  ll operator*(P b) const { return x * b.x + y * b.y; }  // Dot
  ll operator^(P b) const { return x * b.y - y * b.x; }  // Cross
};
P a[kN];

vector<int> solve(P p, P q, vector<int>& idx) {
  int n = int(idx.size());
  if (n == 0) return {};

  // printf("id: ");
  // for(int i : idx) printf("%d ", i); puts("");
  vector<P> vp(n), vq(n);
  for (int i = 0; i < n; i++) {
    vp[i] = a[idx[i]] - p;
    vq[i] = a[idx[i]] - q;
  }
  // printf("vp:\n");
  // for(int i = 0; i < n; i++) printf("%lld %lld\n", vp[i].x, vp[i].y);
  // printf("vq:\n");
  // for(int i = 0; i < n; i++) printf("%lld %lld\n", vq[i].x, vq[i].y);

  vector<int> ord_p(n), ord_q(n);
  vector<int> ord_lis(n);
  for (int i = 0; i < n; i++) {
    ord_p[i] = ord_q[i] = ord_lis[i] = i;
  }
  sort(ord_p.begin(), ord_p.end(),
       [&](int x, int y) { return (vp[x] ^ vp[y]) > 0; });
  sort(ord_q.begin(), ord_q.end(),
       [&](int x, int y) { return (vq[x] ^ vq[y]) < 0; });

  // printf("ord_p: ");
  // for(int i = 0; i < n; i++) printf("%d ", ord_p[i]); puts("");
  // printf("ord_q: ");
  // for(int i = 0; i < n; i++) printf("%d ", ord_q[i]); puts("");

  vector<int> pi(n), qi(n);
  int num = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || (vp[ord_p[i]] ^ vp[ord_p[i - 1]]) != 0) num++;
    pi[ord_p[i]] = num;
  }
  num = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0 || (vq[ord_q[i]] ^ vq[ord_q[i - 1]]) != 0) num++;
    qi[ord_q[i]] = num;
  }
  // printf("pi: ");
  // for(int i = 0; i < n; i++) printf("%d ", pi[i]); puts("");
  // printf("qi: ");
  // for(int i = 0; i < n; i++) printf("%d ", qi[i]); puts("");

  sort(ord_lis.begin(), ord_lis.end(), [&](int x, int y) {
    if (pi[x] != pi[y]) return pi[x] < pi[y];
    return qi[x] > qi[y];
  });
  // printf("ord_lis: ");
  // for(int i = 0; i < n; i++) printf("%d ", ord_lis[i]); puts("");
  vector<int> v(n + 5, 1e9);
  vector<int> dp(n);
  for (int i = 0; i < n; i++) {
    int id = ord_lis[i];
    int val = qi[id];
    int k = lower_bound(v.begin(), v.end(), val) - v.begin();
    dp[i] = k + 1, v[k] = val;
  }
  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, dp[i]);
  // printf("dp: ");
  // for(int i = 0; i < n; i++) printf("%d ", dp[i]); puts("");

  vector<vector<pii>> dp_val(n + 1);
  for (int i = 0; i < n; i++) dp_val[dp[i]].push_back({i, ord_lis[i]});

  vector<int> res;
  for (int i = ans, now = n; i >= 1; i--) {
    pii mn = pii(now, kInf);
    for (auto s : dp_val[i]) {
      if (s.F > now) break;
      int val = (now == n) ? kInf : qi[ord_lis[now]];
      if ((mn.S == kInf || qi[s.S] < val) && mn.S > s.S) mn = s;
    }
    now = mn.F;
    // printf("now = %d, mn.S = %d\n", now, mn.S);
    res.push_back(idx[mn.S]);
  }
  return res;
}
int main() {
  int T;
  scanf("%d", &T);
  int cas = 0;
  while (T--) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    P p(x1, y1), q(x2, y2);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld%lld", &a[i].x, &a[i].y);
    }
    printf("Case #%d: ", ++cas);

    vector<int> L, R;
    for (int i = 1; i <= n; i++) {
      int64_t val = (q - p) ^ (a[i] - p);
      if (val > 0)
        L.push_back(i);
      else if (val < 0)
        R.push_back(i);
    }
    vector<int> resL = solve(p, q, L);
    vector<int> resR = solve(q, p, R);

    vector<int> ans;
    if (int(resL.size()) != int(resR.size())) {
      if (int(resL.size()) > int(resR.size()))
        ans = resL;
      else
        ans = resR;
    } else
      ans = min(resL, resR);
    if (resL.empty()) ans = resR;
    if (resR.empty()) ans = resL;
    printf("%d\n", int(ans.size()));
    for (int x : ans) printf("%d\n", x);
  }

  return 0;
}
