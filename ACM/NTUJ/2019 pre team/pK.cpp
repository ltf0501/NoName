#include <bits/stdc++.h>
using namespace std;

const int MAXN = int(2E5 + 10);

int par[MAXN], sz[MAXN], mxSz[MAXN], depth[MAXN];
vector<int> g[MAXN], cent[MAXN];

void init(int x, int p, int d = 0) {
    par[x] = p;
    depth[x] = d;
    for (int y: g[x]) {
        if (y == par[x]) continue;
        init(y, x, d + 1);
    }
    g[x].resize(remove(g[x].begin(), g[x].end(), par[x]) - g[x].begin());
}

void dfs(int x) {
    sz[x] = 1;
    if (g[x].size() == 0) {
        cent[x] = vector<int>{x};
        return;
    }
    for (int y: g[x]) dfs(y);
    vector<int> tmp{x}, tmp2;
    for (int i = 0; i < int(g[x].size()); i++) {
        sz[x] += sz[g[x][i]];
        mxSz[x] = max(mxSz[x], sz[g[x][i]]);
        int p1 = *tmp.begin(), p2 = *cent[g[x][i]].begin();
        for (int p: { p1, p2 }) {
                    bool get = false;
            for (; p != x; p = par[p]) {
                if (max(mxSz[p], sz[x] - sz[p]) * 2 <= sz[x]) {
                    tmp2.push_back(p);
                                        get = true;
                } else if (get) {
                                    break;
                                }
            }
        }
        if (mxSz[x] * 2 <= sz[x]) tmp2.push_back(x);
        sort(tmp2.begin(), tmp2.end(), [&](int l, int r) { return depth[l] > depth[r]; });
        swap(tmp, tmp2);
        tmp2.clear();
    }
    cent[x] = tmp;
}

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        g[x].push_back(y), g[y].push_back(x);
    }
    init(1, 1);
    dfs(1);
    for (int i = 1; i <= n; i++) {
        sort(cent[i].begin(), cent[i].end());
        cout<<cent[i][0];
        for(int j=1;j<cent[i].size();j++)cout<<" "<<cent[i][j];
        cout<<endl;
    }
}
