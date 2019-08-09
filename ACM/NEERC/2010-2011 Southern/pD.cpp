#include <queue>
#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=1e3+10;
const int INF=1e9+10;
vector<int> graph[N];
int p[N],f[N][N][2];
bool debug=false;
int dp(int pos,int t,int player){
	if(f[pos][t][player]!=-1)return f[pos][t][player];
	int ans=-1;
	for(int i:graph[pos])if(p[i]>t){
		if(dp(i,t+1,1-player)==player){
			ans=player;
			break;
		}
	}
	if(ans==-1)ans=1-player;
	if(debug)printf("dp(%d,%d,%d)=%d\n",pos,t,player,ans);
	return f[pos][t][player]=ans;
}
int main(){
	if(!debug)freopen("input.txt","r",stdin);
	if(!debug)freopen("output.txt","w",stdout);
	int l,r,n,m,now;
	bool went[N];
	queue<int> q;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)p[i]=INF;
	for(int i=1;i<=n;i++)went[i]=false;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=0;k<2;k++)f[i][j][k]=-1;
	went[1]=true;
	p[1]=1;
	q.push(1);
	while(m--){
		scanf("%d%d",&l,&r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	while(!q.empty()){
		now=q.front();
		q.pop();
		for(int i:graph[now])if(!went[i]){
			went[i]=true;
			p[i]=p[now]+1;
			q.push(i);
		}
	}
	now=dp(1,1,0);
	if(now==0)printf("Vladimir\n");
	else printf("Nikolay\n");
}
