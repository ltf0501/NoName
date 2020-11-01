#include <bits/stdc++.h>
using namespace std;


tuple<int, int, int> p[105];
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n, m; scanf("%d%d", &n, &m);
        bool flag[3] = {};
        for(int i = 0; i < m; i++) {
            int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
            p[i] = make_tuple(a, b, c);
            if(a == 0 || b == 0 || c == 0) flag[0] = 1;
            if(a > n || a < -n || b > n || b < -n || c > n || c < -n) flag[1] = 1;
            if(a == b || b == c || c == a) flag[2] = 1;
            if(a == -b || b == -c || c == -a) flag[2] = 1;
        }
        
        if(flag[0]) {
            puts("INVALID: NULL RING");
            continue;
        }
        if(flag[1]) {
            puts("INVALID: RING MISSING");
            continue;
        }
        if(flag[2]) {
            puts("INVALID: RUNE CONTAINS A REPEATED RING");
            continue;
        }

        mt19937 rng;    
        vector<int> id(m);
        for(int i = 0; i < m; i++) id[i] = i;
        shuffle(id.begin(), id.end(), rng);

        vector<int> v(1 << n);
        for(int i = 0; i < (1 << n); i++) v[i] = i;
        shuffle(v.begin(), v.end(), rng);

        bool has_ans = 0;

        auto Check = [&](int a, int b, int c, int x) {
            if(a > 0) {
                if(x & (1 << (a - 1))) return 1;
            }
            else {
                a = -a;
                if(!(x & (1 << (a - 1)))) return 1;
            }

            if(b > 0) {
                if(x & (1 << (b - 1))) return 1;
            }
            else {
                b = -b;
                if(!(x & (1 << (b - 1)))) return 1;
            }

            if(c > 0) {
                if(x & (1 << (c - 1))) return 1;
            }
            else {
                c = -c;
                if(!(x & (1 << (c - 1)))) return 1;
            }
            return 0;
        };
        for(int x : v) {
            bool ok = 1;
            for(int i : id) {
                int a, b, c;
                tie(a, b, c) = p[i];
                if(!Check(a, b, c, x)) {
                    ok = 0; break;
                }
            }
            if(ok) {
                has_ans = 1;
                break;
            }
        }

        if(has_ans) {
            puts("RUNES SATISFIED!");
        }
        else {
            puts("RUNES UNSATISFIABLE! TRY ANOTHER GATE!");
        }
    }
    return 0;
}
