#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
const int K = 1e3 + 10;
const int MOD = 1e9 + 7;
int dp[N][2];
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n, k, nxt, cost[26], ans = 0;
  bool f = true;
  string a, b;
  cin >> k >> n;
  for (int i = 0; i < 26; i++) cin >> cost[i];
  cin >> a >> b;
  for (int i = 0; i <= n; i++) dp[i][0] = dp[i][1] = 0;
  dp[0][0] = 1;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      if (a[i] == b[j]) {
        nxt = j + cost[b[j] - 'A'] + 1;
        if (nxt > n) nxt = n;
        dp[nxt][f] = (dp[nxt][f] + dp[j][!f]) % MOD;
      }
      dp[j + 1][!f] = (dp[j + 1][!f] + dp[j][!f]) % MOD;
      dp[j][!f] = 0;
    }
    dp[n][!f] = 0;
    f = !f;
  }
  for (int i = 0; i <= n; i++) ans = (ans + dp[i][!f]) % MOD;
  cout << ans << endl;
}
