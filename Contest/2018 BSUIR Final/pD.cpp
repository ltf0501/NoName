#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second

int n, k;
vector<int> v;
vector<int> card[kN];
vector<int> dp[kN];  // start from the jth card of ith player
vector<pii> nxt[kN];
vector<pii> pos[kN << 1];
struct P {
  int ans, x, y;
};
P seg[kN << 2];
P push_up(P l, P r) {
  if (l.ans > r.ans) return l;
  return r;
}
void update(int p, P x, int l = 0, int r = n - 1, int o = 1) {
  if (l == r) {
    seg[o] = x;
    return;
  }
  int m = (l + r) >> 1;
  if (p <= m)
    update(p, x, l, m, o << 1);
  else
    update(p, x, m + 1, r, o << 1 | 1);
  seg[o] = push_up(seg[o << 1], seg[o << 1 | 1]);
}
P query(int ql, int qr, int l = 0, int r = n - 1, int o = 1) {
  if (ql <= l && r <= qr) return seg[o];
  int m = (l + r) >> 1;
  if (qr <= m) return query(ql, qr, l, m, o << 1);
  if (ql > m) return query(ql, qr, m + 1, r, o << 1 | 1);
  P le = query(ql, qr, l, m, o << 1);
  P ri = query(ql, qr, m + 1, r, o << 1 | 1);
  return push_up(le, ri);
}
P query2(int l, int r) {
  if (l <= r)
    return query(l, r);
  else {
    P a = query(l, n - 1);
    P b = query(0, r);
    return push_up(a, b);
  }
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    int num;
    scanf("%d", &num);
    card[i].resize(num);
    for (int j = 0; j < num; j++) {
      scanf("%d", &card[i][j]);
      v.push_back(card[i][j]);
    }
    sort(card[i].begin(), card[i].end());
    card[i].resize(unique(card[i].begin(), card[i].end()) - card[i].begin());
    int sz = int(card[i].size());
    dp[i].resize(sz);
    nxt[i].resize(sz);
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < int(card[i].size()); j++) {
      card[i][j] = lower_bound(v.begin(), v.end(), card[i][j]) - v.begin();
      pos[card[i][j]].push_back({i, j});
    }
  }

  for (int i = int(v.size()) - 1; i >= 0; i--) {
    for (pii p : pos[i]) {
      int l = (p.F + 1) % n, r = (p.F + k + 1) % n;
      P res = query2(l, r);
      dp[p.F][p.S] = res.ans + 1;
      nxt[p.F][p.S] = pii(res.x, res.y);
    }
    for (pii p : pos[i]) {
      update(p.F, {dp[p.F][p.S], p.F, p.S});
    }
  }

  int ans = 0;
  pii now = {-1, -1};
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j < int(dp[i].size()); j++) {
      if (dp[i][j] > ans) {
        ans = dp[i][j], now = pii(i, j);
      }
    }
  }
  printf("%d\n", ans);
  for (int i = 0; i < ans; i++) {
    printf("%d %d\n", now.F + 1, v[card[now.F][now.S]]);
    now = nxt[now.F][now.S];
  }
  return 0;
}
