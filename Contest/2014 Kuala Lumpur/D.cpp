#include <bits/stdc++.h>
using namespace std;
const int kN = 2e4 + 10;

int n;
vector<int> g[kN];
int SG[kN];

void Dfs(int u) {
    if(g[u].empty()) {
        SG[u] = 0;
        return;
    }
    vector<int> tmp;
    for(int v : g[u]) {
        Dfs(v);
        tmp.push_back(SG[v]);
    }
    sort(tmp.begin(), tmp.end());
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
    SG[u] = int(tmp.size());
    for(int i = 0; i < int(tmp.size()); i++) {
        if(tmp[i] != i) {
            SG[u] = i;
            break;
        }
    }
}

void Init() {
    for(int i = 1; i <= n; i++) g[i].clear();
}
int main() {
    int T; scanf("%d", &T);
    int cas = 0;
    while(T--) {
        scanf("%d", &n);
        Init();
        vector<int> c(n + 1);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &c[i]);
        }
        for(int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            if(x != 0) g[x].push_back(i);
        }

        Dfs(1);
        int res = 0;
        for(int i = 1; i <= n; i++)
            if(c[i] & 1) res ^= SG[i];
        printf("Case #%d: ", ++cas);
        puts(res ? "first" : "second");
    }
    return 0;
}
