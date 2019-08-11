#include <bits/stdc++.h>
using namespace std;

pair<int, int> p[3000], p2[3000];

int64_t cross(pair<int, int> a, pair<int, int> b) {
    return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
    if (n <= 2) {
        cout << "0\n";
        return 0;
    }
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {
        auto o = p[i];
        copy(p, p + n, p2);
        if (i != 0) swap(p2[i], p2[0]);
        auto cmp = [&](pair<int, int> l, pair<int, int> r) {
            auto lo = make_pair(l.first - o.first, l.second - o.second);
            auto ro = make_pair(r.first - o.first, r.second - o.second);
            if (lo.second < 0 || (lo.second == 0 && lo.first < 0)) {
                lo.first *= -1, lo.second *= -1;
            }
            if (ro.second < 0 || (ro.second == 0 && ro.first < 0)) {
                ro.first *= -1, ro.second *= -1;
            }
            return cross(lo, ro) > 0;
        };
        sort(p2 + 1, p2 + n, cmp);
        int64_t acc = 1;
        for (int j = 2; j < n; j++) {
            if (!cmp(p2[j - 1], p2[j]) && !cmp(p2[j], p2[j - 1])) {
                acc++;
            } else {
                ans += acc * (n - acc - 1);
                acc = 1;
            }
        }
        ans += acc * (n - acc - 1);
    }
    assert(ans % 6 == 0);
    cout << ans / 6 << '\n';
}
