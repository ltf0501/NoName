#include <bits/stdc++.h>
using namespace std;

int a[100010], b[100010];

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  int64_t ans[3] = {}, bsum[3] = {};
  for (int i = 1; i <= n; i++) bsum[i % 3] += b[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      ans[(i + j) % 3] += 1LL * a[i] * bsum[j];
    }
  }
  cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << '\n';
}
