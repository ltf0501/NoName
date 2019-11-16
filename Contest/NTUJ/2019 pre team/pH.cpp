#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef pair<int,int> pii;
const int maxn=320;
const int N=110;
const int inf=1e9+10;
struct Edge {
        int from, to, cap, flow, cost;
        Edge(){}
        Edge(int u, int v, int c, int f, int co): from(u), to(v), cap(c), flow(f), cost(co){}
};

vector<Edge> edges;
vector<int> G[maxn];

struct MCMF {
        int n, m, s, t;
        int dis[maxn];
        int h[maxn];
        int p[maxn];

        void init(int n) {
                this->n = n;
                for(int i = 0; i < n; i++) G[i].clear();
                edges.clear();
        }

        void AddEdge(int from, int to, int cap, int cost) {
                edges.push_back(Edge(from, to, cap, 0, cost));
                edges.push_back(Edge(to, from, 0, 0, -cost));
                m = (int)edges.size();
                G[from].push_back(m - 2);
                G[to].push_back(m - 1);
        }

        bool dijkstra(int s, int t, int& max_flow, long long& cost) {
                priority_queue<pii, vector<pii>, greater<pii> > pq;
                for(int i = 0; i < n; i++) dis[i] = inf;
                dis[s] = 0, pq.push(pii(0, s));
                while(!pq.empty()) {
                        pii u = pq.top(); pq.pop();
                        int v = u.S;
                        if(dis[v] < u.F) continue;
                        for(int i = 0; i < (int)G[v].size(); i++) {
                                Edge& e = edges[G[v][i]];
                                if(e.cap > e.flow && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {
                                        dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
                                        p[e.to] = G[v][i];
                                        pq.push(pii(dis[e.to], e.to));
                                }
                        }
                }
                if(dis[t] == inf) return 0;
                for(int i = 0; i < n; i++) h[i] += dis[i];
                int d = max_flow;
                for(int u = t; u != s; u = edges[p[u]].from)
                        d = min(d, edges[p[u]].cap - edges[p[u]].flow);
                max_flow -= d;
                cost += (long long)d * (long long)h[t];
                for(int u = t; u != s; u = edges[p[u]].from) {
                        edges[p[u]].flow += d;
                        edges[p[u]^1].flow -= d;
                }
                return 1;
        }

        bool MincostMaxflow(int s, int t, int max_flow, long long& cost) {
                this->s = s, this->t = t;
                cost = 0;
                for(int i = 0; i < n; i++) h[i] = 0;
                while(dijkstra(s, t, max_flow, cost) && max_flow);
                return max_flow==0;
        }
};
int main(){
    MCMF solver;
    int s,t,n,m,k,L[N],R[N],x[N],y[N],l[N],r[N],c[N];
    long long int cost;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d%d",&L[i],&R[i]);
    scanf("%d",&m);
    for(int i=0;i<m;i++)scanf("%d%d",&x[i],&y[i]);
    scanf("%d",&k);
    for(int i=0;i<k;i++)scanf("%d%d%d",&l[i],&r[i],&c[i]);
    s=0,t=n+m+k+1;
    solver.init(t+1);
    for(int i=0;i<m;i++)solver.AddEdge(n+i+1,t,1,0);
    for(int i=0;i<n;i++)solver.AddEdge(s,i+1,1,0);
    for(int i=0;i<k;i++)solver.AddEdge(s,n+m+i+1,1,c[i]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(!(L[i]>y[j]||x[j]>R[i]))solver.AddEdge(i+1,n+j+1,1,0);
    for(int i=0;i<k;i++)for(int j=0;j<m;j++)if(!(l[i]>y[j]||x[j]>r[i]))solver.AddEdge(n+m+i+1,n+j+1,1,0);
    if(solver.MincostMaxflow(s,t,m,cost))printf("%lld\n",cost);
    else printf("-1\n");
}
