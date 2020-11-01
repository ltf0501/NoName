#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(1E6 + 10);
typedef long long int ll;

ll h, b, t, x, y, z;
ll dp[kN];

ll callen(ll hei) {
    ll ans = (t * (hei) + b * (h - hei)) / h;
    return ans;
}

ll cal(ll len, ll sz) {
    return (len / sz) * (len / sz); 
}

int main() {
    while (scanf("%lld%lld%lld%lld%lld%lld", &h, &b, &t, &x, &y, &z) != EOF) {
        dp[0] = 0;
        for (int i = 1; i <= h; i++) {
            dp[i] = dp[i - 1];
            if (i >= x) dp[i] = max(dp[i], dp[i - x] + cal(callen(i), x) * x * x * x);
            if (i >= y) dp[i] = max(dp[i], dp[i - y] + cal(callen(i), y) * y * y * y);
            if (i >= z) dp[i] = max(dp[i], dp[i - z] + cal(callen(i), z) * z * z * z);
        }
        printf("%lld\n", dp[h]);
    }
}
