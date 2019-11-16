#include <stdio.h>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 1e5 + 10;
int a[N], left[N], right[N], n;
int dis(int l, int r) {
  if (r > l)
    return r - l;
  else
    return n - (l - r);
}
void pre() {
  stack<pair<int, int>> s;
  for (int i = 1; i <= n; i++) {
    while (!s.empty()) {
      if (s.top().F > a[i]) {
        right[s.top().S] = i;
        s.pop();
      } else
        break;
    }
    if (!s.empty()) left[i] = s.top().S;
    s.push({a[i], i});
  }
  for (int i = 1; i <= n; i++) {
    while (!s.empty()) {
      if (s.top().F > a[i]) {
        right[s.top().S] = i;
        s.pop();
      } else
        break;
    }
    if (!s.empty()) left[i] = s.top().S;
    s.push({a[i], i});
  }
  // printf("a:: ");
  // for(int i=1;i<=n;i++)printf("%d ",a[i]);
  // printf("\nleft:: ");
  // for(int i=1;i<=n;i++)printf("%d ",left[i]);
  // printf("\nright:: ");
  // for(int i=1;i<=n;i++)printf("%d ",right[i]);
  // printf("\n");
  return;
}
int main() {
  int A, B, C, ans = N + N;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  pre();
  for (int i = 1; i <= n; i++)
    if (left[i] != 0 && right[i] != 0 &&
        dis(left[i], i) + dis(i, right[i]) < ans) {
      ans = dis(left[i], i) + dis(i, right[i]);
      A = left[i];
      B = i;
      C = right[i];
    }
  printf("%d %d %d\n", A, B, C);
}
