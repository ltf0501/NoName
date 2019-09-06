#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m;
vector<int> g[maxn];
char t(char c) {
        return 'R' + 'B' - c;
}
int id(int x, char c) {
        return (x << 1) | (c == 'R');
}
int in[maxn], dfs_clock;
int sccno[maxn], scc_cnt;
vector<int> scc[maxn];
stack<int> s;
int col[maxn];
int dfs(int u) {
        s.push(u);
        int lowu = in[u] = ++dfs_clock;
        for(int v : g[u]) {
                if(!in[v]) lowu = min(lowu, dfs(v));
                else if(!sccno[v]) lowu = min(lowu, in[v]);
        }
        if(lowu == in[u]) {
                scc_cnt++;
                while(1) {
                        int x = s.top(); s.pop();
                        scc[scc_cnt].push_back(x);
                        sccno[x] = scc_cnt;
                        if(x == u) break;
                }
        }
        return lowu;
}
int main() {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; i++) {
                int x, y, z;
                char a[2], b[2], c[2];
                scanf("%d %s %d %s %d %s", &x, a, &y, b, &z, c);
                x--, y--, z--;
                g[id(x, t(a[0]))].push_back(id(y, b[0]));
                g[id(x, t(a[0]))].push_back(id(z, c[0]));
                g[id(y, t(b[0]))].push_back(id(x, a[0]));
                g[id(y, t(b[0]))].push_back(id(z, c[0]));
                g[id(z, t(c[0]))].push_back(id(x, a[0]));
                g[id(z, t(c[0]))].push_back(id(y, b[0]));
        }
        for(int i = 0; i < 2 * n; i++)
                if(!in[i]) dfs(i);
        for(int i = 0; i < 2 * n; i += 2) {
                if(sccno[i] == sccno[i ^ 1]) return 0 * puts("-1");
        }
        for(int i = 1; i <= scc_cnt; i++) {
                if(!col[i]) {
                        col[i] = 1;
                        for(int x : scc[i]) col[sccno[x ^ 1]] = 2;
                }
        }
        for(int i = 0; i < 2 * n; i += 2) {
                if(col[sccno[i]] == 1) putchar('B');
                else putchar('R');
        }
        puts("");
        return 0;
}
