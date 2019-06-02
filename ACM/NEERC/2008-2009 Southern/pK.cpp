#include <queue>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N=5e1+10;
const int INF=1e9+10;
struct edge{
	int to,rev,cap;
};
int dep[N],iter[N],went[N];
vector<edge> graph[N];
int min(int a,int b){return a>b?b:a;}
void addedge(int u,int v,int cap){
	graph[u].PB({v,(int)graph[v].size(),cap});
	graph[v].PB({u,(int)graph[u].size()-1,0});
	return ;
}
void bfs(int s,int cnt){
	int nxt;
	queue<int> q;
	dep[s]=iter[s]=0;
	went[s]=cnt;
	q.push(s);
	while(!q.empty()){
		nxt=q.front();
		q.pop();
		for(edge i:graph[nxt])if(i.cap>0&&went[i.to]!=cnt){
			went[i.to]=cnt;
			iter[i.to]=0;
			q.push(i.to);
			dep[i.to]=dep[nxt]+1;
		}
	}
	return ;
}
int dfs(int u,int t,int nv){
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
	for(int i=0;i<N;i++)went[i]=-1;
	while(true){
		bfs(s,cnt);
		if(went[t]!=cnt++)break;
		while((f=dfs(s,t,INF))!=0)ans+=f;
	}
	return ans;
}
void dfs1(int pos){
	if(went[pos]!=0)return ;
	went[pos]=1;
	for(edge i:graph[pos])if(i.cap>0)dfs1(i.to);
	return ;
}
int main(){
	int n,m,s,l,r,k,val=INF,mc,mt,temp,ms;
	vector<pair<pair<int,int>,int>>mg[N],ng[N];
	vector<int> ans;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&k);
		mg[l].PB({{r,k},i});
		mg[r].PB({{l,k},i});
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)ng[j].clear();
		for(int j=1;j<=n;j++)if(i!=j)for(pair<pair<int,int>,int> k:mg[j])if(k.F.F!=i)ng[j].PB(k);
		s=i==1?2:1;
		for(int j=1;j<=n;j++)if(j!=s&&j!=i){
			for(int k=1;k<=n;k++)graph[k].clear();
			for(int k=1;k<=n;k++)for(pair<pair<int,int>,int> p:ng[k])addedge(k,p.F.F,p.F.S);
			temp=dinic(s,j);
			if(temp<val){
				val=temp;
				mt=j;
				ms=s;
				mc=i;
			}
		}
	}
	for(int i=1;i<=n;i++)ng[i].clear(),graph[i].clear();
	for(int i=1;i<=n;i++)if(i!=mc)for(pair<pair<int,int>,int> j:mg[i])if(j.F.F!=mc)ng[i].PB(j);
	for(int i=1;i<=n;i++)for(pair<pair<int,int>,int> j:ng[i])addedge(i,j.F.F,j.F.S);
	dinic(ms,mt);
	for(int i=1;i<=n;i++)went[i]=0;
	dfs1(ms);
	for(int i=1;i<=n;i++)if(went[i]==1)for(pair<pair<int,int>,int> j:ng[i])if(went[j.F.F]==0)ans.PB(j.S);
	printf("%d\n",val);
	if(ans.empty())printf("0\n\n");
	else{
		sort(ans.begin(),ans.end());
		printf("%d\n%d",(int)ans.size(),ans[0]);
		for(int i=1;i<ans.size();i++)printf(" %d",ans[i]);
		printf("\n");
	}
}
