#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 10;
int w[maxn], d[maxn], st[maxn];
vector<int> ans[maxn], v[maxn];
struct P {
    int num, id;
    bool operator < (const P& c) const {
        return num < c.num;
    }
};
int main() {
    int n, m, W, H;
    scanf("%d%d%d%d", &m, &n, &W, &H);
    for(int i = 1; i <= m; i++) scanf("%d", &w[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &d[i]), st[i] = d[i];
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= min(n, i + W - 1); j++) st[j] -= st[i]; 
    for(int i = 1; i <= n; i++) if(st[i] < 0 ) return 0 * puts("-1");
    for(int i = n; i > n - W + 1; i--) if(st[i] > 0) return 0 * puts("-1"); 
//  for(int i = 1; i <= n; i++) printf("%d ", st[i]); puts("");
    priority_queue<P> pq;
    for(int i = 1; i <= m; i++) pq.push({w[i], i});
    for(int i = 1; i <= n; i++) {
        for(int j : v[i]) pq.push({w[j], j});
        while(st[i]--) {
            if(pq.empty()) return 0 * puts("-1");
            auto x = pq.top(); pq.pop();
            ans[x.id].push_back(i);
            if(i + W + H <= n) v[i + W + H].push_back(x.id);
            w[x.id] -= W;
        }
    }
    for(int i = 1; i <= m; i++)
        if(w[i]) return 0 * puts("-1");
    puts("1");
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < (int)ans[i].size(); j++)
            printf("%d%c", ans[i][j], j == (int)ans[i].size() - 1 ? '\n' : ' ');
    }
    return 0;
}
