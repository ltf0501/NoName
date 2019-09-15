#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
vector<int> fac(ll n) {
    vector<int> res;
    while(n) res.push_back(n % 7), n /= 7;
    return res;
}
ll pw[50];
int pre[7];
int main() {
    pre[0] = 1, pre[1] = 3, pre[2] = 6, pre[3] = 10, pre[4] = 15, pre[5] = 21, pre[6] = 28;
    pw[0] = 1;
    for(int i = 1; i < 50; i++) pw[i] = pw[i - 1] * 28 % mod;
    int T, cas = 0;
    scanf("%d", &T);
    while(T--) {
        ll n;
        scanf("%lld", &n);
        if(!n) {
            printf("Case %d: 0\n", ++cas);
            continue;   
        }
        ll ans;
        if(n & 1) ans = 1LL * ((n + 2) % mod) * (((n + 1) / 2) % mod) % mod;
        else ans = 1LL * ((n + 1) % mod) * (((n + 2) / 2) % mod) % mod;
        //printf("ans = %lld\n", ans);
        vector<int> v = fac(n);
        ll tmp = 0, cur = 1;
        for(int i = (int)v.size() - 1; i >= 0; i--) {
            int x = v[i];
            if(i != 0 && x == 0) continue;
            if(i != 0) {

                //printf("pos(%d) = %d, %lld\n", i, x, cur * pw[i] * pre[x - 1] % mod); 

                tmp = (tmp + cur * pw[i] % mod * pre[x - 1] % mod) % mod;   
                cur = cur * (x + 1) % mod;
            }
            else {
                //printf("pos(%d) = %d, %lld\n", i, x, cur * pw[i] * pre[x] % mod); 
                tmp = (tmp + cur * pw[i] % mod * pre[x] % mod) % mod;   
            }
        }
        ans = (ans - tmp) % mod;
        if(ans < 0) ans += mod;
        printf("Case %d: %lld\n", ++cas, ans);
    }
    return 0;
}
