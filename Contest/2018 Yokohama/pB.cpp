#include <stdio.h>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int N = 5e3 + 10;
bool used[N][N];
int max(int a, int b) { return a > b ? a : b; }
int main() {
  int n, a[N], temp, last, ans = 0, now;
  map<int, int> m;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  sort(a, a + n);
  for (int i = 0; i < n; i++) m[a[i]] = i;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) used[i][j] = false;
  for (int i = 0; i < n; i++)
    if (n - i + 1 > ans)
      for (int j = 0; j < i; j++)
        if (!used[i][j]) {
          used[i][j] = true;
          last = i;
          now = 2;
          while (m.find(a[last] + a[i] - a[j]) != m.end()) {
            temp = m[a[last] + a[i] - a[j]];
            used[temp][last] = true;
            last = temp;
            now++;
          }
          ans = max(ans, now);
        }
  printf("%d\n", ans);
}
