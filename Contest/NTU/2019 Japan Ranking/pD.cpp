bool debug=false;
#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
const int N=2e3+10;
const int INF=1e9+10;
#define PB push_back
struct edge{
    int to,rev,cap;
};
vector<edge> graph[N];
int iter[N],dep[N],went[N];
void addedge(int u,int v,int cap){
    graph[u].PB({v,(int)graph[v].size(),cap});
    graph[v].PB({u,(int)graph[u].size()-1,0});
    return ;
}
void bfs(int s,int t){
    queue<int> q;
    int nxt;
    iter[s]=dep[s]=0;
    went[s]=t;
    q.push(s);
    while(!q.empty()){
        nxt=q.front();
        q.pop();
        for(edge i:graph[nxt])if(went[i.to]!=t&&i.cap>0){
            dep[i.to]=dep[nxt]+1;
            went[i.to]=t;
            iter[i.to]=0;
            q.push(i.to);
        }
    }
    return ;
}
int min(int a,int b){return a>b?b:a;}
int dfs(int u,int t,int nv){
    if(debug)printf("dfs(%d,%d,%d)\n",u,t,nv);
    if(u==t)return nv;
    int temp;
    for(int &i=iter[u];i<graph[u].size();i++){
        edge& nxt=graph[u][i];
        if(nxt.cap>0&&dep[nxt.to]>dep[u]){
            temp=dfs(nxt.to,t,min(nv,nxt.cap));
            if(temp>0){
                nxt.cap-=temp;
                graph[nxt.to][nxt.rev].cap+=temp;
                return temp;
            }
        }
    }
    return 0;
}
int dinic(int s,int t){
    int ans=0,cnt=0,f;
    for(int i=0;i<N;i++)went[i]=0;
    while(true){
        bfs(s,++cnt);
        if(went[s]!=went[t])break;
        while((f=dfs(s,t,INF))>0)ans+=f;
    }
    return ans;
}
int max(int a,int b){return a>b?a:b;}
int main(){
    int s=0,temp,t,hpos,k,wpos,cpos,mpos,h,w,c,m,nw,nc,nm,tot;
    scanf("%d%d%d%d%d%d%d",&h,&w,&c,&m,&nw,&nc,&nm);
    hpos=1;
    wpos=hpos+h+1;
    cpos=wpos+w+1;
    mpos=cpos+c+1;
    t=mpos+m+1;
    tot=t+1;
    for(int i=0;i<h;i++)addedge(s,hpos+i,1);
    for(int i=0;i<h;i++)addedge(hpos+i,hpos+i+tot,1);
    for(int i=0;i<h;i++)addedge(hpos+i+tot,wpos+w,1);
    for(int i=0;i<w;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&temp);
            temp--;
            addedge(hpos+temp+tot,wpos+i,1);
        }
    }
    for(int i=0;i<w;i++)addedge(wpos+i,wpos+i+tot,1);
    addedge(wpos+w,wpos+w+tot,nw);
    for(int i=0;i<w;i++)addedge(wpos+i+tot,cpos+c,1);
    for(int i=0;i<c;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&temp);
            temp--;
            addedge(wpos+temp+tot,cpos+i,1);
        }
    }
    for(int i=0;i<c;i++)addedge(wpos+w+tot,cpos+i,1);
    for(int i=0;i<c;i++)addedge(cpos+i,cpos+i+tot,1);
    addedge(cpos+c,cpos+c+tot,nc);
    if(debug)printf("cdone\n");
    for(int i=0;i<m;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&temp);
            temp--;
            addedge(cpos+temp+tot,mpos+i,1);
        }
    }
    if(debug)printf("mdone\n");
    for(int i=0;i<c;i++)addedge(cpos+i+tot,mpos+m,1);
    for(int i=0;i<m;i++)addedge(cpos+c+tot,mpos+i,1);
    for(int i=0;i<m;i++)addedge(mpos+i,mpos+i+tot,1);
    addedge(mpos+m,mpos+m+tot,nm);
    for(int i=0;i<m;i++)addedge(mpos+i+tot,t,1);
    addedge(mpos+m+tot,t,nm);
    if(debug)printf("s=%d t=%d tot=%d\n",s,t,tot);
    if(debug){
    
    }
    printf("%d\n",dinic(s,t));
}
