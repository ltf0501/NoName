#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=1e5+10;
bool vis[N],ok[N];
double sz[N];
int hei[N];
vector<int> graph[N],ng[N];
int max(int a,int b){return a>b?a:b;}
void dfs(int pos){
	vis[pos]=true;
	hei[pos]=0;
	sz[pos]=1;
	for(int i:graph[pos])if(!vis[i])dfs(i);
	for(int i:graph[pos])sz[pos]+=sz[i];
	for(int i:graph[pos])hei[pos]=max(hei[pos],hei[i]);
	hei[pos]++;
	return ;
}
void solve(int n){
	int pos=1,ans=0,m,l,r,temp=0,npos=1;
	scanf("%d",&m);
	for(int i=1;i<=n;i++)graph[i].clear();
	for(int i=1;i<=n;i++)ng[i].clear();
	while(m--){
		scanf("%d%d",&l,&r);
		graph[l].PB(r);
		ng[r].PB(l);
	}
	for(int i=1;i<=n;i++)vis[i]=false;
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	for(int i=2;i<=n;i++)if(sz[i]>sz[pos])pos=i;
	for(int i=1;i<=n;i++)vis[i]=false;
	dfs(pos);
	for(int i=1;i<=n;i++)if(vis[i])ans++;
	for(int i=1;i<=n;i++)if(hei[i]>hei[npos])npos=i;
	for(int i=1;i<=n;i++)vis[i]=false;
	dfs(npos);
	temp=0;
	for(int i=1;i<=n;i++)if(vis[i])temp++;
	if(temp>ans){
		ans=temp;
		pos=npos;
	}
	printf("%d %d\n",pos,ans);
}
int main(){
    freopen("journey.in","r",stdin);
    freopen("journey.out","w",stdout);
	int n;
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		else solve(n);
	}
}
