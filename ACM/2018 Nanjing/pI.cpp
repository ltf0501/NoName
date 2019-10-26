#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
struct edge{
	int to,rev,cap;
};
const int N=2e3+10;
const int INF=1e9+10;
vector<edge> graph[N];
int dep[N],iter[N],went[N];
void addedge(int u,int v,int cap){
	graph[u].PB({v,(int)graph[v].size(),cap});
	graph[v].PB({u,(int)graph[u].size()-1,0});
	return ;
}
void bfs(int s,int t){
	int nxt;
	queue<int> q;
	dep[s]=iter[s]=0;
	went[s]=t;
	q.push(s);
	while(!q.empty()){
		nxt=q.front();
		q.pop();
		for(edge i:graph[nxt])if(i.cap>0&&went[i.to]!=t){
			went[i.to]=t;
			q.push(i.to);
			dep[i.to]=dep[nxt]+1;
			iter[i.to]=0;
		}
	}
	return ;
}
int min(int a,int b){return a>b?b:a;}
int dfs(int u,int t,int nv){
	if(u==t)return nv;
	int temp;
	for(int &i=iter[u];i<graph[u].size();i++){
		edge& nxt=graph[u][i];
		if(nxt.cap>0&&dep[nxt.to]>dep[u]){
			temp=dfs(nxt.to,t,min(nxt.cap,nv));
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
	int ans=0,f,cnt=0;
	for(int i=0;i<N;i++)went[i]=cnt;
	while(true){
		bfs(s,++cnt);
		if(went[s]!=went[t])break;
		while((f=dfs(s,t,INF))>0)ans+=f;
	}
	return ans;
}
int main(){
	int n,m,k,s=0,t,cnt,temp;
	scanf("%d%d%d",&n,&m,&k);
	t=n+m+1;
	for(int i=1;i<=n;i++)addedge(s,i,1),addedge(t+1,i,1);
	addedge(s,t+1,k);
	for(int i=1;i<=m;i++)addedge(i+n,t,1);
	for(int i=1;i<=n;i++){
		scanf("%d",&cnt);
		while(cnt--){
			scanf("%d",&temp);
			addedge(i,temp+n,1);
		}
	}
	printf("%d\n",dinic(s,t));
}
