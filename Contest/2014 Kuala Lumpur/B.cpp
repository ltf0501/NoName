#include <bits/stdc++.h>
using namespace std;
const int kN = 1e4 + 10;
const int kMod = 1e9 + 7;
const int inv2 = 5e8 + 4;

int fpow(int a, int n) {
    //printf("a = %d, n = %d\n", a, n);
    if(a < 0) a += kMod;
    int res = 1;
    while(n) {
        if(n & 1) res = 1LL * res * a % kMod;
        n >>= 1, a = 1LL * a * a % kMod;
    }
    //printf("res = %d\n", res);
    return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}
int fac[kN], invf[kN];
void pre() {
    fac[0] = 1;
    for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
    invf[kN - 1] = Inv(fac[kN - 1]);
    for(int i = kN - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % kMod;
}

int C(int n, int m) {
    //printf("n = %d, m = %d\n", n, m);
    if(n < m) return 0;
    return 1LL * fac[n] * invf[m] % kMod * invf[n - m] % kMod;
}

int add(int a, int b) {
    a += b;
    if(a >= kMod) a -= kMod;
    return a;
}
int main() {
    pre();
    int T; scanf("%d", &T);
    int cas = 0;
    while(T--) {
        int n, k; scanf("%d%d", &n, &k);
        int a = 0, b = 0;
        for(int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            if(!x) a++;
            else b++;
        }
        // find x^{k - b} in (1 + x^2 + x^4 + ...)^n
        
        printf("Case #%d: ", ++cas);
        if(k < b || ((k - b) & 1)) {
            puts("0"); continue;
        }
        int ans = 0;

        //printf("a = %d, b = %d\n", a, b);
        for(int t = 0; t <= n; t++) {
            int tmp = 0;
            for(int i = 0; i <= t; i++) {
                int ttmp = 1LL * C(a, i) * C(b, t - i) % kMod;
                //printf("i = %d, ttmp = %d\n", i, ttmp);
                if((t - i) & 1) ttmp = (kMod - ttmp) % kMod;
                tmp = add(tmp, ttmp);
            }
            //printf("t = %d, tmp = %d\n", t, tmp);
            tmp = 1LL * tmp * fpow(n - 2 * t,  k) % kMod;
            //printf("tmp = %d\n", tmp);
            ans = add(ans, tmp);
        }
        //ans = 2LL * ans % kMod;
        ans = 1LL * ans * fpow(inv2, n) % kMod % kMod;
        printf("%d\n", ans);
    }
    return 0;
}
