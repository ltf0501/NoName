#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
bool have[10];

void cal(ll n) {
    if (n == 0) have[0] = true;
    else {
        while (n) {
            have[n % 10] = true;
            n /= 10;
        }
    }
    return ;
}

void solve(ll n) {
    int ans = 0, x = n;
    bool f;
    for (int i = 0; i < 10; i++) have[i] = false;
    while (true) {
        cal(n);
        ans++;
        f = false;
        for (int i = 0; i < 10; i++) if (!have[i]) f = true;
        n += x;
        if (!f) break;
    }
    printf("%d\n", ans);
    return ;
}

int main() {
    ll n;
    while (scanf("%lld", &n) != EOF) solve(n);
}
