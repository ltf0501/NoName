#include <bits/stdc++.h>
using namespace std;

int cycle[200], wake[200], dp[200][200];

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) cin >> cycle[i];
    int n; cin >> n;
    for (int i = 0; i <= 150; i++) wake[i] = 24;
    for (int i = 0; i < n; i++) {
        int d, m; cin >> d >> m;
        wake[d] = min(wake[d], m);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i <= 150; i++) {
        for (int j = 0; j < t; j++) {
            if (wake[i] < cycle[j]) dp[i][j] = 0x3f3f3f3f;
            int &a1 = dp[i + 1][(j + 1) % t];
            a1 = min(a1, dp[i][j]);
            auto &a2 = dp[i + 1][0];
            a2 = min(a2, dp[i][j] + 1);
        }
    }
    cout << *min_element(dp[150], dp[150] + t) << '\n';
}
