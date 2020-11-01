#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(5E2 + 10);

int n, m, val[kN][kN];
bool board[kN][kN];
bitset<kN> m_board[kN], bs;
string s[kN];

void solve() {
    int h, w, g = 0, l = 0;
    cin >> h >> w;
    int x = 0, y = 0, ans = 0; 
    for (int i = 0; i < h; i++) cin >> s[i];
    for (int i = 0; i < h; i++) for (int j = 0; j < kN; j++) m_board[i][j] = true;
    for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) m_board[i][j] = (s[i][j] == 'G');
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) val[i][j] = 0;

    for (int i = 0; i + h <= n; i++) {
        for (int ni = 0; ni < h; ni++) {
            bs.reset();
            for (int j = 0; j < w; j++) bs[j] = board[i + ni][j];
            val[i][0] += kN - (bs ^ m_board[ni]).count();
            for (int j = 1; j + w <= m; j++) {
                bs >>= 1;
                bs[kN - 1] = false;
                bs[w - 1] = board[i + ni][j + w - 1];
                val[i][j] += kN - (bs ^ m_board[ni]).count();
            }
        }
    }

    //cout << '\n';

    //for (int i = 0; i < n; i++, cout << '\n') for (int j = 0; j < m; j++) cout << val[i][j] << ' '; 

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (val[i][j] > ans) {
        ans = val[i][j];
        x = i, y = j;
    }

    for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) if (m_board[i][j] && board[i + x][j + y]) g++;
    else if (!m_board[i][j] && !board[i + x][j + y]) l++;

    cout << x + 1 << " " << y + 1 << " " << g << " " << l << '\n';
    return ;
}

int main() {
    int b;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) board[i][j] = (s[i][j] == 'G');
    cin >> b;
    for (int i = 1; i <= b; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
