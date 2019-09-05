#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct P {
    int a, b, c;
};
vector<P> ans;
bool vis[maxn];
int in[maxn], dfs_clock;
vector<int> g[maxn];
int n, m;
bool dfs(int u, int fa) {
    vis[u] = 1;
    in[u] = ++ dfs_clock;
    int ch = -1;
    for(int v : g[u]) if(v != fa) {
        if(in[v] > in[u]) continue;
        if(!vis[v]) {
            if(!dfs(v, u)) {
                if(ch != -1) ans.push_back({ch, u, v}), ch = -1;
                else ch = v;
            }
        }
        else {
            if(ch != -1) ans.push_back({ch, u, v}), ch =-1;
            else ch = v;
        }
    }
    if(ch == -1) return 0;
    if(fa != -1) ans.push_back({ch, u, fa});
    return 1;
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);  
    }
    for(int i = 1; i <= n; i++)
        if(!vis[i]) dfs(i, -1);
    printf("%d\n", (int)ans.size());
    for(auto p : ans) printf("%d %d %d\n", p.a, p.b, p.c);
    return 0;
}
