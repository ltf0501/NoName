#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(5E3 + 10);

int deg[kN];
bool need[kN];
vector<int> graph[kN];

void solve() {
    int n, m, cnt = 0, tmp, l, r;
    ll ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) graph[i].clear();
    for (int i = 1; i <= m; i++) {
        cin >> l >> r;
        graph[l].PB(r);
        graph[r].PB(l);
    }
    for (int i = 1; i <= n; i++) deg[i] = int(graph[i].size());
    cnt = n * (n - 1) - m * 2;
    for (int i = 1; i <= n; i++) {
        for (int j : graph[i]) need[j] = true;
        need[i] = true;
        for (int j : graph[i]) cnt -= (n - 1 - deg[j]) << 1;
        for (int j : graph[i]) {
            tmp = 0;
            for (int k : graph[j]) if (need[k]) tmp++;
            cnt += (deg[i] - tmp);
        }
        cnt -= (n - 1 - deg[i]) << 1;
        ans += cnt;
        cnt += (n - 1 - deg[i]) << 1;
        for (int j : graph[i]) cnt += (n - 1 - deg[j]) << 1;
        for (int j : graph[i]) {
            tmp = 0;
            for (int k : graph[j]) if (need[k]) tmp++;
            cnt -= (deg[i] - tmp);
        }
        for (int j : graph[i]) need[j] = false;
        need[i] = false;
    }
    cout << ans / 6 << '\n';
}

int main() {
    int t;
    string s;
    cin >> t;
    getline(cin, s);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
