#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
const int INF = 1e9 + 7;
int pre_max[maxn];
int a[maxn];
int n, q;
int seg[maxn << 2];
void push_up(int o) { seg[o] = max(seg[o << 1], seg[o << 1 | 1]); }
void build(int l, int r, int o) {
  if (l == r) {
    seg[o] = a[l];
    return;
  }
  int m = (l + r) >> 1;
  build(l, m, o << 1), build(m + 1, r, o << 1 | 1);
  push_up(o);
}
int query(int l, int r, int o, int ql, int qr) {
  if (ql > r || qr < l) return -1;
  if (ql <= l && r <= qr) return seg[o];
  int m = (l + r) >> 1;
  if (qr <= m) return query(l, m, o << 1, ql, qr);
  if (ql > m) return query(m + 1, r, o << 1 | 1, ql, qr);
  return max(query(l, m, o << 1, ql, qr), query(m + 1, r, o << 1 | 1, ql, qr));
}
int dp[maxn], nxt[maxn];
int cnt[maxn];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), pre_max[i] = max(pre_max[i - 1], a[i]);
    for (int i = 1; i <= n; i++) {
      cnt[i] = cnt[i - 1];
      if (a[i] > pre_max[i - 1]) cnt[i]++;
    }
    a[n + 1] = INF;
    stack<int> s;
    s.push(n + 1);
    for (int i = n; i >= 1; i--) {
      while (a[i] >= a[s.top()]) s.pop();
      nxt[i] = s.top();
      s.push(i);
    }
    memset(dp, 0, sizeof(dp));
    //		for(int i=1;i<=n;i++)printf("%d ",nxt[i]);puts("");
    for (int i = n; i >= 1; i--) dp[i] = dp[nxt[i]] + 1;
    build(1, n, 1);
    while (q--) {
      int p, x;
      scanf("%d%d", &p, &x);
      if (x > pre_max[p - 1]) {
        int l = p + 1, r = n;
        while (l < r) {
          int m = (l + r) >> 1;
          if (query(1, n, 1, p + 1, m) > x)
            r = m;
          else
            l = m + 1;
        }
        if (l == n && query(1, n, 1, p + 1, n) <= x) l = n + 1;
        int id = l;
        //				printf("Xid = %d\n",id);
        printf("%d\n", cnt[p - 1] + 1 + dp[id]);
      } else {
        int l = p + 1, r = n;
        while (l < r) {
          int m = (l + r) >> 1;
          if (query(1, n, 1, p + 1, m) > pre_max[p - 1])
            r = m;
          else
            l = m + 1;
        }
        if (l == n && query(1, n, 1, p + 1, n) <= pre_max[p - 1]) l = n + 1;
        int id = l;
        //				printf("Oid = %d\n",id);
        printf("%d\n", cnt[p - 1] + dp[id]);
      }
    }
  }
  return 0;
}
