#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 9;
const int maxn = 2e5 + 10;
int a[maxn];
ll one[maxn << 2], two[maxn << 2], thr[maxn << 2];
struct P {
    ll p[3];
};
void push_up(int o) {
    one[o] = (one[o << 1] + one[o << 1 | 1]) % mod;
    two[o] = (one[o << 1] * one[o << 1 | 1] % mod + two[o << 1] + two[o << 1 | 1]) % mod;
    thr[o] = (one[o << 1] * two[o << 1 | 1] % mod + one[o << 1 | 1] * two[o << 1] % mod + thr[o << 1] + thr[o << 1 | 1]) % mod; 
}
void build(int l, int r, int o) {
    if(l == r) {
        one[o] = a[l];
        two[o] = 0;
        thr[o] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(l, m, o << 1), build(m + 1, r, o << 1 | 1);
    push_up(o);
}
void update(int l, int r, int o, int p, int x) {
    if(l == r) {
        one[o] = x;
        two[o] = 0;
        thr[o] = 0;
        return;
    }
    int m = (l + r) >> 1;
    if(p <= m) update(l, m, o << 1, p, x);
    else update(m + 1, r, o << 1 | 1, p, x);
    push_up(o);
}
P query(int l, int r, int o, int ql, int qr) {
    if(ql <= l && r <= qr) return {one[o], two[o], thr[o]};
    int m = (l + r) >> 1;
    if(qr <= m) return query(l, m, o << 1, ql, qr);
    if(ql > m) return query(m + 1, r, o << 1 | 1, ql, qr);
    P left = query(l, m, o << 1, ql, qr);
    P right = query(m + 1, r, o << 1 | 1, ql, qr);
    return {(left.p[0] + right.p[0]) % mod, (left.p[1] + right.p[1] + left.p[0] * right.p[0] % mod) %mod, (left.p[2] + right.p[2] + left.p[0] * right.p[1] % mod + left.p[1] * right.p[0] % mod) % mod};
}
int Log(int x, int e) {
    double a = log(x), b = log(e);
    return int(a / b);
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, n, 1);
    set<int> s;
    for(int i = 1; i <= n; i++) 
        if(a[i] > 0)s.insert(i);
    s.insert(n + 1);
    while(q--) {
        int type;
        scanf("%d", &type);
        if(type == 1) {
            int l, r, e;
            scanf("%d%d%d", &l, &r, &e);
            vector<int> v;
            auto it = s.lower_bound(l);
            while(*it <= r) {
                int y = Log(a[*it], e);
                if(y == 0) v.push_back(*it);
                update(1, n, 1, *it, y);
                a[*it] = y;             
                it++;
            }
            for(int i : v) s.erase(i);
        }
        else if(type == 2) {
            int x, y;
            scanf("%d%d", &x, &y);
            update(1, n, 1, x, y);
            s.insert(x);
            a[x] = y;
        }
        else {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, n, 1, l, r).p[2]);
        }
    }   
    return 0;
}
