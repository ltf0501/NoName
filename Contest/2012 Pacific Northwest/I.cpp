#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = int(1E3 + 10), kInf = int(1E9 + 10);
int anc[kN];
double p[kN], e[kN];

void solve(int n, int P, int E) {
    vector<double> v;
    double c;
    double np, ne;
    int now, l, r, mid;
    for (int i = 1; i <= n; i++) scanf("%lf%lf%d", &p[i], &e[i], &anc[i]);
    for (int i = 1; i <= n; i++) {
        np = p[i], ne = e[i];
        v.PB(ne / np);
        now = i;
        while (anc[now] != 0) {
            np -= p[now] / 2;
            now = anc[now];
            np += p[now], ne += e[now];
            v.PB(ne / np);
        }
    }
    sort(v.begin(), v.end());
    c = v.back();
    //printf("c = %.20lf\n", c);
    //l = 0, r = kInf;
    //while (r - l > 1) {
    //  mid = (l + r) >> 1;

    //
    //}
    //printf("%d\n", r);
    printf("%.0lf\n", max(ceil((log(E * c) - log(P * c * c)) / c), 0.0));
    return ;
}

int main() {
    int n, P, E;
    while (true) {
        scanf("%d%d%d", &n, &P, &E);
        if (n == 0 && P == 0 && E == 0) break;
        solve(n, P, E);
    }
}
