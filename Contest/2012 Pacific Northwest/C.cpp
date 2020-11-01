#include <bits/stdc++.h>
using namespace std;
constexpr int kN = (1 << 26) * 20;
#define F first
#define S second
int n, m;
set<int> went;
vector<string> field;
bool Input() {
    string line;
    field.clear();
    m = -1;
    while (getline(cin, line) && !line.empty()) {
        if (m == -1) m = int(line.size());
        field.push_back(line);
        assert(int(line.size()) == m);
    }
    n = int(field.size());
    if (field.empty()) return false;
    return true;
}
int posx[20], posy[20], cnt;

struct Status {
    int x, y;
    bool dicecolor[6], color[20];
    // dicecolor {top, down, right, left, up, bottom}
    int Hash() {
        int ans = 0;
        for (int i = 0; i < 6; i++) if (dicecolor[i]) ans = ans << 1 | 1;
        else ans = ans << 1;
        for (int i = 0; i < cnt; i++) if (color[i]) ans = ans << 1 | 1;
        else ans = ans << 1;
        ans = ans * cnt;
        for (int i = 0; i < cnt; i++) if (posx[i] == x && posy[i] == y) ans += i; 
        return ans;
    }
    bool godown() {
        if (x + 1 >= n) return false;
        if (field[x + 1][y] == '#') return false;
        x++;
        bool tmp[6];
        tmp[0] = dicecolor[4];
        tmp[1] = dicecolor[0];
        tmp[2] = dicecolor[2];
        tmp[3] = dicecolor[3];
        tmp[4] = dicecolor[5];
        tmp[5] = dicecolor[1];
        for (int i = 0; i < 6; i++) dicecolor[i] = tmp[i];
        return true;
    }
    bool goup() {
        if (x - 1 < 0) return false;
        if (field[x - 1][y] == '#') return false;
        x--;
        bool tmp[6];
        tmp[0] = dicecolor[1];
        tmp[1] = dicecolor[5];
        tmp[2] = dicecolor[2];
        tmp[3] = dicecolor[3];
        tmp[4] = dicecolor[0];
        tmp[5] = dicecolor[4];
        for (int i = 0; i < 6; i++) dicecolor[i] = tmp[i];
        return true;
    }
    bool goright() {
        if (y + 1 >= m) return false;
        if (field[x][y + 1] == '#') return false;
        y++;
        bool tmp[6];
        tmp[0] = dicecolor[3];
        tmp[1] = dicecolor[1];
        tmp[2] = dicecolor[0];
        tmp[3] = dicecolor[5];
        tmp[4] = dicecolor[4];
        tmp[5] = dicecolor[2];
        for (int i = 0; i < 6; i++) dicecolor[i] = tmp[i];
        return true;
    }
    bool goleft() {
        if (y - 1 < 0) return false;
        if (field[x][y - 1] == '#') return false;
        y--;
        bool tmp[6];
        tmp[0] = dicecolor[2];
        tmp[1] = dicecolor[1];
        tmp[2] = dicecolor[5];
        tmp[3] = dicecolor[0];
        tmp[4] = dicecolor[4];
        tmp[5] = dicecolor[3];
        for (int i = 0; i < 6; i++) dicecolor[i] = tmp[i];
        return true;
    }
};

bool isp[20];

int main() {
    int dis, g, c, tmp;
    bool f, found;
    queue<pair<Status, int>> q;
    Status cur, nxt;
    while (Input()) {
        went.clear();
        cnt = 0;
        for (int i = 0; i < 20; i++) isp[i] = false;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
            if (field[i][j] != '#') {
                posx[cnt] = i, posy[cnt] = j;
                if (field[i][j] == 'P') isp[cnt] = true;
                else if (field[i][j] == 'G') g = cnt;
                else if (field[i][j] == 'C') c = cnt;
                cnt++;
            }
        memset(&cur, 0, sizeof(cur));
        memset(&nxt, 0, sizeof(nxt));
        cur.x = posx[c], cur.y = posy[c];
        //for (int i = 0; i < 6; i++) cur.dicecolor[i] = true;
        for (int i = 0; i < cnt; i++) if (isp[i]) cur.color[i] = true;
        went.insert(cur.Hash());
        q.push(make_pair(cur, 0));

        found = false;

        function<bool(Status)> go = [&](Status nnxt) {
            tmp = nnxt.Hash();
            if (went.find(tmp) == went.end()) {
                went.insert(tmp);
                for (int i = 0; i < cnt; i++) if (posx[i] == nnxt.x && posy[i] == nnxt.y) {
                    swap(nnxt.dicecolor[5], nnxt.color[i]);
                }
                f = (nnxt.x == posx[g] && nnxt.y == posy[g]);
                for (int i = 0; i < 6; i++) if (!nnxt.dicecolor[i]) f = false;
                if (f) {
                    cout << dis + 1 << '\n';
                    return true;
                }
                q.push(make_pair(nnxt, dis + 1));
            }
            return false;
        };

        while (!q.empty()) {
            cur = q.front().F;
            dis = q.front().S;
            q.pop();
            //cout << cur.x << ' ' << cur.y << '\n';
            //for (int i = 0; i < 6; i++) cout << (cur.dicecolor[i] ? 1 : 0);
            //cout << '\n';
            //for (int i = 0; i < cnt; i++) cout << (cur.color[i] ? 1 : 0);
            //cout << '\n';
            //cout << "now dis = " << dis << '\n';
            nxt = cur;
            if (nxt.godown()) { 
                if (go(nxt)) {
                    found = true;
                    break;
                }
            }
            nxt = cur;
            if (nxt.goup()) {
                if (go(nxt)) {
                    found = true;
                    break;
                }
            }
            nxt = cur;
            if (nxt.goright()) {
                if (go(nxt)) {
                    found = true;
                    break;
                }
            }
            nxt = cur;
            if (nxt.goleft()) {
                if (go(nxt)) {
                    found = true;
                    break;
                }
            }
        }

        if (found) {
            while (!q.empty()) q.pop();
        }
        else cout << -1 << '\n';

    }
}
