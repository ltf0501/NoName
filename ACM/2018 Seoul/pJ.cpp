#include <bits/stdc++.h>
using namespace std;

bool vis[1010][1010], human[1010], alien[1010], mil[1010];
vector<int> s_human, s_alien, g[1010][21];

int main() {
        int n, w, c, h, m; cin >> n >> w >> c >> h >> m;    
        for (int i = 0; i < h; i++) {
                int x; cin >> x;
                human[x] = true;
        }
        for (int i = 0; i < m; i++) {
                int x; cin >> x;
                mil[x] = true;
        }
        for (int x = 0; x < n; x++) {
                if (human[x]) s_human.push_back(x);
                else s_alien.push_back(x);
        }
        for (int i = 0; i < w; i++) {
                int s, c, t; cin >> s >> c >> t;
                g[s][c].push_back(t);
        }
        queue<pair<int, int>> q;
        for (auto x: s_human) {
                for (auto y: s_alien) {
                        vis[x][y] = true;
                        q.emplace(x, y);
                }
        }
        while (q.size()) {
                auto cur = q.front(); q.pop();
                if (mil[cur.first] && mil[cur.second]) {
                        cout << "YES\n";
                        return 0;
                }
                for (int i = 1; i <= c; i++) {
                        for (auto nxt_x: g[cur.first][i]) {
                                for (auto nxt_y: g[cur.second][i]) {
                                        if (!vis[nxt_x][nxt_y]) {
                                                vis[nxt_x][nxt_y] = true;
                                                q.emplace(nxt_x, nxt_y);
                                        }
                                }
                        }
                }
        }
        cout << "NO\n";
}
