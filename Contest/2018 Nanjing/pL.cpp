#include <bits/stdc++.h>
using namespace std;
constexpr int kN = 5001;
int16_t a[kN], dp[kN][kN][3][1 << 2];
void upd(int16_t &d, int x) { d = min(d, int16_t(x)); }
int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  int n, x, y;
  cin >> n >> x >> y;
  int16_t cnt[3] = {};
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    a[i] = k == x ? 0 : k == y ? 1 : 2;
    ++cnt[a[i]];
  }
  if (!cnt[0] || !cnt[1]) {
    cout << "0\n";
    return 0;
  }
  if (!cnt[2]) {
    cout << "-1\n";
    return 0;
  }
  int16_t ans = int16_t(min(cnt[0], cnt[1]) + 1);
  for (int i = 1; i < n; i++) {
    if (a[i - 1] == 2 && a[i] == 2) ans = min({ans, cnt[0], cnt[1]});
  }
  if (a[0] == 2 || a[n - 1] == 2) ans = min({ans, cnt[0], cnt[1]});
  memset(dp, 0x3f, sizeof(dp));
  dp[0][0][2][0] = cnt[2];
  for (int i = 0; i < n; i++) {
    if (a[i] == 2) {
      for (int j = 0; j <= cnt[2]; j++) {
        for (int k = 0; k < 4; k++) {
          // Place 2
          upd(dp[i + 1][j + 1][2][k], dp[i][j][0][k] - 1);
          upd(dp[i + 1][j + 1][2][k], dp[i][j][1][k] - 1);
          upd(dp[i + 1][j + 1][2][k], dp[i][j][2][k] - 1);
          // Not place 2
          upd(dp[i + 1][j][0][k], dp[i][j][0][k]);
          upd(dp[i + 1][j][1][k], dp[i][j][1][k]);
          upd(dp[i + 1][j][2][k], dp[i][j][2][k]);
        }
      }
    } else {
      for (int j = 0; j <= cnt[2]; j++) {
        for (int l = 0; l < 3; l++) {
          // Place 2 before the current element
          upd(dp[i + 1][j + 1][a[i]][0], dp[i][j][l][0]);
          upd(dp[i + 1][j + 1][a[i]][1], dp[i][j][l][1]);
          upd(dp[i + 1][j + 1][a[i]][2], dp[i][j][l][2]);
          upd(dp[i + 1][j + 1][a[i]][3], dp[i][j][l][3]);
          // Remove the current element
          upd(dp[i + 1][j][l][0], dp[i][j][l][0] + 1);
          upd(dp[i + 1][j][l][1], dp[i][j][l][1] + 1);
          upd(dp[i + 1][j][l][2], dp[i][j][l][2] + 1);
          upd(dp[i + 1][j][l][3], dp[i][j][l][3] + 1);
          if (1 - a[i] != l) {
            // Do nothing
            upd(dp[i + 1][j][a[i]][(0 | 1 << a[i]) & 0x3], dp[i][j][l][0]);
            upd(dp[i + 1][j][a[i]][(1 | 1 << a[i]) & 0x3], dp[i][j][l][1]);
            upd(dp[i + 1][j][a[i]][(2 | 1 << a[i]) & 0x3], dp[i][j][l][2]);
            upd(dp[i + 1][j][a[i]][(3 | 1 << a[i]) & 0x3], dp[i][j][l][3]);
          }
        }
      }
    }
  }
  upd(ans,
      min({dp[n][cnt[2]][0][3], dp[n][cnt[2]][1][3], dp[n][cnt[2]][2][3]}));
  cout << ans << '\n';
}
