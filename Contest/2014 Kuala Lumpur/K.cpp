#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 2e4 + 10;

ll n;
int S;
char c[kN];
int x[kN], y[kN];
ll pw[41];

void update(int id) {
    for(int i = 0; i < S; i++) y[i] = (x[i] + x[(i + pw[id]) % S]) % 3;
    for(int i = 0; i < S; i++) x[i] = y[i];
}
int main() {
    pw[0] = 1;
    for(int i = 1; i <= 38; i++) pw[i] = 3 * pw[i - 1];
    //printf("%lld ", pw[38]);
    int T; scanf("%d", &T);
    int cas = 0;
    while(T--) {
        scanf("%s %lld", c, &n);
        S = strlen(c);
        auto GetID = [&](char cc) {
            if(cc == 'W') return 0;
            if(cc == 'R') return 1;
            return 2;
        };
        for(int i = 0; i < S; i++) x[i] = GetID(c[i]);
        
        int id = 38;
        while(id >= 0) {
            while(pw[id] <= n) {
                update(id);
                n -= pw[id];
            }
            id--;
        }
        int cnt[3] = {};
        for(int i = 0; i < S; i++) cnt[x[i]]++;
        printf("Case #%d: ", ++cas);
        for(int i = 0; i < 3; i++) printf("%d ", cnt[i]); puts("");
    }
    return 0;
}
