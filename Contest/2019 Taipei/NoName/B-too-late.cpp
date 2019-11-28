bool debug=false;
#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=1e5+10;
vector<int> graph[N];
bool color[N],black[N],nb[N];
int need[N];
void dfs(int pos,int from){
	nb[pos]=black[pos]=color[pos]=false;
	need[pos]=0;
	for(int i:graph[pos])if(i!=from)dfs(i,pos);
	for(int i:graph[pos])if(i!=from)need[pos]+=need[i];
	for(int i:graph[pos])if(i!=from){
		if(nb[i])nb[i]=true;
		else if(need[i]==0)black[pos]=true;
	}
	if(need[pos]==0){
		if(!black[pos])need[pos]=1;
	}
	else if(need[pos]==1){
		if(!black[pos])need[pos]=1;
		else{
			nb[pos]=true;
			need[pos]=0;
		}
	}
	else {
		color[pos]=black[pos]=true;
		nb[pos]=false;
		need[pos]=0;
	}
	return ;
}
int main(){
	int n,l,r,ans=0;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&l,&r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	dfs(1,0);
	if(!black[1])color[1]=true;
	if(debug){
		for(int i=1;i<=n;i++)printf("%d ",color[i]?1:0);
		printf("\n");
		for(int i=1;i<=n;i++)printf("%d ",black[i]?1:0);
		printf("\n");
		for(int i=1;i<=n;i++)printf("need[%d]=%d\n",i,need[i]);
	}
	for(int i=1;i<=n;i++)if(color[i])ans++;
	printf("%d\n",ans);
}
