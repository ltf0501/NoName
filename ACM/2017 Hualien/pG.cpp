#include <bits/stdc++.h>
using namespace std;
int64_t ans[50000], w[50000], d[50000];
vector<pair<int64_t, int64_t>> line;
constexpr __float128 INF = 1e18;
using ll = long long;
struct Line {
    static bool flag;
    ll a, b;
    __float128 l, r;
    int64_t operator()(__float128 x) const { return a * x + b; }
    bool operator<(const Line &rhs) const {
        return flag ? a < rhs.a || (a == rhs.a && b < rhs.b) : l < rhs.l;
    }
};
__float128 intersect(Line p, Line q) {
    assert(p.a != q.a);
    return __float128(q.b - p.b) / __float128(p.a - q.a);
}
bool Line::flag = 1;
struct ConvexHull {
    set<Line> lines_;
    ConvexHull() { Line::flag = 1; }
    void init() { lines_.clear(); }
    void insert(ll a, ll b) {
        Line now = {a, b, -INF, INF};
        if (lines_.empty()) {
            lines_.insert(now);
            return;
        }
        Line::flag = 1;
        auto it = lines_.lower_bound(now);
        auto prv = (it == lines_.begin()) ? it : prev(it);
        if (it != lines_.end()) {
            if (it == lines_.begin() && it->a == now.a) return;
            __float128 x = it->l;
            if (it != lines_.begin() && now(x) <= (*it)(x)) return;
        }
        if (it != lines_.begin()) {
            while (prv != lines_.begin() && (*prv)(prv->l) <= now(prv->l)) {
                prv = --lines_.erase(prv);
            }
            if (prv == lines_.begin() && now.a == prv->a) lines_.erase(prv);
        }
        if (it != lines_.end()) {
            while (it != --lines_.end() && (*it)(it->r) <= now(it->r)) {
                it = lines_.erase(it);
            }
        }
        if (it != lines_.begin()) {
            prv = prev(it);
            __float128 x = intersect(*prv, now);
            const_cast<Line*>(&*prv)->r = now.l = x;
        }
        if (it != lines_.end()) {
            __float128 x = intersect(now, *it);
            const_cast<Line*>(&*it)->l = now.r = x;
        }
        lines_.insert(now);
    }
    __float128 query(__float128 a) {
        if (lines_.empty()) return -INF;
        Line::flag = 0;
        auto it = --lines_.upper_bound({0, 0, a, 0});
        return (*it)(a);
    }
};
int main() {
    cin.tie(0), ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i = 0; i < n; i++) cin >> w[i];
        for (int i = 0; i < n; i++) cin >> d[i];
        ConvexHull l_h, r_h;
        for (int i = 0; i < n; i++) {
            ans[i] = 0.5 + l_h.query(d[i]);
            l_h.insert(w[i], w[i] * d[i]);
        }
        for (int i = n - 1; i >= 0; i--) {
            ans[i] = max(ans[i], int64_t(0.5 + r_h.query(d[i])));
            r_h.insert(w[i], w[i] * d[i]);
        }
        --k;
        //for (int i = 0; i < n; i++) cerr << ans[i] << ' ';
        //cerr << '\n';
        nth_element(ans, ans + k, ans + n);;
        cout << ans[k] << '\n';
    }
}
