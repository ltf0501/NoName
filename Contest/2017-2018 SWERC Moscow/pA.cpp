#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N = 2e3 + 10;
int main() {
  int n, m, a[N], b[N], pos = 0, ans = 0;
  map<int, int> ma;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (b[j] >= a[i]) ma[b[j] - a[i]]++;
  for (pair<int, int> i : ma)
    if (i.S > ans) {
      ans = i.S;
      pos = i.F;
    }
  printf("%d\n", pos);
}
