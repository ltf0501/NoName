#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = int(1E5 + 10);
int p[kN];
vector<tuple<int, int, int>> edges;

int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}

void solve() {
    int n, m, ans = 0, mx = 0, u, v, c;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;
    edges.clear();
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> c;
        edges.PB(make_tuple(c, u, v));
    }
    sort(edges.begin(), edges.end(), greater<tuple<int, int, int>>());
    for (tuple<int, int, int> i : edges) {
        u = get<1>(i), v = get<2>(i);
        if (Find(u) == Find(v)) {
            mx = max(mx, get<0>(i));
            ans += get<0>(i);
        }
        else p[Find(u)] = Find(v);
    }
    cout << " " << ans << " " << mx << '\n';
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ":";
        solve();
    }
}
