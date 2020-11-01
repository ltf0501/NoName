#include <bits/stdc++.h>

using namespace std;

#define PB push_back
#define F first
#define S second
constexpr int kN = int(1E3 + 10);
vector<pair<int, int>> graph[kN];
vector<int> ng[kN];
bool can[kN], inq[kN];
int dist[kN], cnt[kN];

void dfs(int pos) {
    can[pos] = true;
    for (int i : ng[pos]) if (!can[i]) dfs(i);
    return ;
}

bool solve() {
    int n, m, l, r, c;
    pair<int, int> cur;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < n; i++) ng[i].clear();
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &l, &r, &c);
        graph[l].PB({r, c});
        ng[r].PB(l);
    }
    for (int i = 0; i < n; i++) can[i] = false;
    for (int i = 0; i < n; i++) inq[i] = false;
    for (int i = 0; i < n; i++) cnt[i] = 0;
    dist[0] = 0;
    for (int i = 1; i < n; i++) dist[i] = 1E9;
    pq.push({0, 0});
    dfs(0);
    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();
        if (dist[cur.S] < cur.F) continue;
        inq[cur.S] = false;
        for (pair<int, int> i : graph[cur.S]) if (dist[i.F] > i.S + cur.F && !inq[i.F]) {
            inq[i.F] = true;
            if (cnt[i.F]++ <= n) {
                dist[i.F] = i.S + cur.F;
                pq.push({dist[i.F], i.F});
            }
        }
    }
    for (int i = 0; i < n; i++) if (inq[i] && can[i]) return true;
    return false;
}


int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        if (solve()) printf("possible\n");
        else printf("not possible\n");
    }
}
