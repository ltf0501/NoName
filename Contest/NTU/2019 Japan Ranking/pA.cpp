#include <bits/stdc++.h>
using namespace std;

int ii[1000], r[1000], o[1000];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> ii[i];
    tuple<long double, int, int, int> ans{};
    get<0>(ans) = INT_MAX;
    for (int a = 0; a < 16; a++) {
        for (int s = 0; s < 16; s++) {
            for (int c = 0; c < 16; c++) {
                r[0] = s;
                for (int nn = 1; nn <= n; nn++) {
                    r[nn] = (a * r[nn - 1] + c) % 256;
                }
                int cnt[256] = {};
                for (int nn = 1; nn <= n; nn++) {
                    o[nn] = (r[nn] + ii[nn]) % 256;
                    cnt[o[nn]]++;
                }
                long double h = 0;
                for (int i = 0; i < 256; i++) {
                    if (cnt[i]) h -= 1.0 * cnt[i] / n * log(1.0 * cnt[i] / n);
                }
                if (abs(h - get<0>(ans)) <= 1e-7) {
                    h = min(h, get<0>(ans));
                }
                ans = min(ans, make_tuple(h, s, a, c));
            }
        }
    }
    cout << get<1>(ans) << ' ' << get<2>(ans) << ' ' << get<3>(ans) << '\n';
}
