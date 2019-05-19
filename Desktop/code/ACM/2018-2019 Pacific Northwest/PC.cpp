#include<bits/stdc++.h>
using namespace std;
const int INF=0x5f5f5f5f;
struct Edge
{
	int from,to, cap;
};
const int maxn=1200;
vector<Edge> edges;
vector<int> gFlow[1200];
int dist[maxn];
int vis[maxn];
int flowS,flowT;
void addEdge(int u,int v,int cap){
	edges.push_back(Edge{u,v,cap});
	gFlow[u].push_back(edges.size()-1);
	edges.push_back(Edge{v,u,0});
	gFlow[v].push_back(edges.size()-1);
	return ;
}
int bfs(){
	memset(dist,0x5f,sizeof(dist));
	dist[flowS]=0;
	queue<int> q;
	q.push(flowS);
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		for(int i:gFlow[cur]){
			Edge &e = edges[i];
			if(e.cap>0&&dist[e.to]==INF){
				dist[e.to]=dist[cur]+1;
				if(e.to==flowT){return dist[e.to];}
				q.push(e.to);
			}
		}
	}
	return INF;
}
int dfs(int cur,int f)
{
	if(cur==flowT)return f;
	vis[cur]=1;
	for(int i : gFlow[cur])
	{
		Edge &e=edges[i];
		if(e.cap>0 && dist[e.to]==dist[cur]+1 && !vis[e.to])
		{
			int newF=dfs(e.to,min(f,e.cap));
			if(newF)
			{
				e.cap-=newF;
				edges[i^1].cap+=newF;
				return newF;
			}

		}
	}
	return 0;
}
int dinic()
{
	int flow=0;
	while(bfs()<INF)
	{
		for(;;)
		{
			memset(vis,0,sizeof(vis));
			int f=dfs(flowS,1<<30);
			if(!f)break;
			flow+=f;
		}
	}
	return flow;
}
const int dx[]={1,-1,0,0,0,0};
const int dy[]={0,0,1,-1,0,0};
const int dz[]={0,0,0,0,1,-1};
bool bad[1500];
int id(int x,int y,int z)
{
	return x*100+y*10+z;
}
bool check(int x,int y,int z)
{
	return x>=0 && x<10 && y>=0 && y<10 && z>=0 && z<10;
}
void init()
{
	memset(bad,0,sizeof(bad));
	for(int i=0;i<maxn;i++)gFlow[i].clear();
	edges.clear();
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		init();
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			bad[id(x,y,z)]=1;
		}	
		flowS=1000,flowT=1001;
		for(int x=0;x<10;x++)for(int y=0;y<10;y++)for(int z=0;z<10;z++)
		{
			if(x==0 || x==9)addEdge(flowS,id(x,y,z),1);
			if(y==0 || y==9)addEdge(flowS,id(x,y,z),1);
			if(z==0 || z==9)addEdge(flowS,id(x,y,z),1);
			if(!bad[id(x,y,z)])
			{
				for(int i=0;i<6;i++)
				{
					int a=x+dx[i],b=y+dy[i],c=z+dz[i];
					if(!check(a,b,c))continue ;
					addEdge(id(x,y,z),id(a,b,c),1);
				}
			}
			else 
			{
				addEdge(id(x,y,z),flowT,INF);
			}
		}		
		printf("%d\n",dinic());
	}
	return 0;
}
