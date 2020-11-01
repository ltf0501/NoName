#include <bits/stdc++.h>
using namespace std;

#define PB push_back
constexpr int kN = int(1E2 + 10);
int tox[kN];
bool connected[kN];
vector<int> graph[kN];
bitset<kN> went;
string s[kN];

bool dfs(int pos) {
    went[pos] = true;
    for (int i : graph[pos]) if (!connected[i]) {
        connected[i] = true;
        tox[i] = pos;
        return true;
    }

    for (int i : graph[pos]) if (!went[tox[i]] && dfs(tox[i])) {
        tox[i] = pos;
        return true;
    }

    return false;
}

void solve() {
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < m; i++) connected[i] = false;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (s[i][j] == '1') {
        graph[i].PB(j);
    }

    for (int i = 0; i < n; i++) {
        went.reset();
        if (dfs(i)) ans++;
    }

    cout << ans << '\n';
    return ;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
