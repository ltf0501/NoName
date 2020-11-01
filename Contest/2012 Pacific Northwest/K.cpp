#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(2E3 + 10), kInf = int(1E9 + 10);
struct Edge {
    int to, rev, cap;
};
vector<Edge> graph[kN];
int dep[kN], went[kN], iter[kN];
void addedge(int u, int v, int c) {
    //printf("addedge(%d, %d, %d)\n", u, v, c);
    graph[u].PB({v, int(graph[v].size()), c});
    graph[v].PB({u, int(graph[u].size()) - 1, 0});
    return ;
}

void Bfs(int s, int t) {
    //printf("Bfs\n");
    queue<int> q;
    int nxt;
    q.push(s);
    went[s] = t;
    iter[s] = dep[s] = 0;
    //printf("s = %d, t = %d\n", s, t);
    while (!q.empty()) {
        nxt = q.front();
        q.pop();
        //printf("nxt = %d\n", nxt);
        for (Edge i : graph[nxt]) if (i.cap > 0 && went[i.to] != t) {
            went[i.to] = t;
            q.push(i.to);
            dep[i.to] = dep[nxt] + 1;
            iter[i.to] = 0;
        }
    }
    return ;
}

int Dfs(int u, int t, int nv) {
    //printf("Dfs\n");
    if (u == t) return nv;
    int tmp;
    for (int &i = iter[u]; i < int(graph[u].size()); i++) {
        Edge& nxt = graph[u][i];
        if (nxt.cap > 0 && dep[nxt.to] > dep[u]) {
            tmp = Dfs(nxt.to, t, min(nxt.cap, nv));
            if (tmp > 0) {
                nxt.cap -= tmp;
                graph[nxt.to][nxt.rev].cap += tmp;
                return tmp;
            }
        }
    }
    return 0;
}

int Dinic(int s, int t) {
    int ans = 0, f, cnt = 0;
    for (int i = 0; i < kN; i++) went[i] = 0;
    while (true) {
        Bfs(s, ++cnt);
        if (went[s] != went[t]) break;
        while ((f = Dfs(s, t, kInf)) > 0) ans += f;
    }
    return ans;
}

vector<string> field;

pair<int, int> Input() {
    int n = 0, m = -1;
    string line;
    field.clear();
    while (getline(cin, line) && !line.empty()) {
        if (m == -1) m = int(line.size());
        field.push_back(line);
        assert(int(line.size()) == m);
    }
    if (field.empty()) return {0, 0};
    return {n = int(field.size()), m};
}

int idx[kN][kN], idx2[kN][kN];

int main() {
    int n, m, cnt, S, T;
    pair<int, int> tmp;
    while (true) {
        tmp = Input();
        if (tmp.F == 0 && tmp.S == 0) break;
        n = tmp.F, m = tmp.S;
        cnt = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) idx[i][j] = cnt++;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) idx2[i][j] = cnt++;
        S = cnt++, T = cnt++;
        for (int i = 0; i <= T; i++) graph[i].clear();
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (field[i][j] == 'W') {
            addedge(S, idx[i][j], 1);
        }
        else if (field[i][j] == 'N') addedge(idx2[i][j], T, 1);
        
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) addedge(idx[i][j], idx2[i][j], 1);


        for (int i = 0; i < n; i++) for (int j = 1; j < m; j++) {
            if (field[i][j] == 'I' && field[i][j - 1] == 'W') addedge(idx2[i][j - 1], idx[i][j], 1);
            if (field[i][j] == 'W' && field[i][j - 1] == 'I') addedge(idx2[i][j], idx[i][j - 1], 1);
            if (field[i][j] == 'I' && field[i][j - 1] == 'N') addedge(idx2[i][j], idx[i][j - 1], 1);
            if (field[i][j] == 'N' && field[i][j - 1] == 'I') addedge(idx2[i][j - 1], idx[i][j], 1);
        }
        for (int i = 1; i < n; i++) for (int j = 0; j < m; j++) {
            if (field[i][j] == 'I' && field[i - 1][j] == 'W') addedge(idx2[i - 1][j], idx[i][j], 1);
            if (field[i][j] == 'W' && field[i - 1][j] == 'I') addedge(idx2[i][j], idx[i - 1][j], 1);
            if (field[i][j] == 'I' && field[i - 1][j] == 'N') addedge(idx2[i][j], idx[i - 1][j], 1);
            if (field[i][j] == 'N' && field[i - 1][j] == 'I') addedge(idx2[i - 1][j], idx[i][j], 1);
        }
        cout << Dinic(S, T) << '\n';
    }
    
}
