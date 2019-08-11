#include <bits/stdc++.h>
using namespace std;
const int mod = 1e8 + 7;
typedef long long ll;
ll f(ll x) {
    ll s = 155136880301 % mod;
    ll k = (s * x % mod * x % mod - 998244353 * x % mod + 71227122) % mod;
    if(k < 0) k += mod;
    return k;
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        ll x;
        scanf("%lld", &x);
        x %= mod;       
        printf("%lld\n", f(x) % mod);
    }
    return 0;
}
