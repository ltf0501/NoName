#include <bits/stdc++.h>
using namespace std;

int cnt[500][500];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void solve() {
    int x, y, n, ans = 0, dir = 0;
    string s;
    cin >> x >> y >> s;
    n = int(s.size());
    memset(cnt, 0, sizeof(cnt));
    x += 200, y += 200;
    cnt[x][y]++;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') {
            x += dx[dir];
            y += dy[dir];
            cnt[x][y]++;
        }
        else if (s[i] == 'L') {
            dir = (dir + 1) % 4;
        }
        else {
            dir = (dir + 3) % 4;
        }
        
    }
    for (int i = 0; i < 500; i++) for (int j = 0; j < 500; j++) if (cnt[i][j] > 1) ans++;
    x -= 200, y -= 200;
    cout << " " << x << " " << y << " " << ans << '\n';
    return ;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ":";
        solve();
    }
}
