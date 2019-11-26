#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=1e3+10;
int ccnt,ans,want;
bool color[N];
vector<int> graph[N];
int n;
int min(int a,int b){return a>b?b:a;}
bool black[N];
bool edge[N][N];
bool check(){
	for(int i=1;i<=n;i++)black[i]=false;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)edge[i][j]=false;
	bool dothing=true;
	for(int i=1;i<=n;i++)if(color[i]){
		black[i]=true;
		for(int j:graph[i]){
			edge[i][j]=edge[j][i]=true;
			black[j]=true;
		}
	}
	while(dothing){
		dothing=false;
		for(int i=1;i<=n;i++)for(int j:graph[i])if(!edge[i][j]){
			if(black[i]&&black[j]){
				edge[i][j]=edge[j][i]=true;
				dothing=true;
				break;
			}
			int cnt=0;
			for(int k:graph[i])if(!edge[i][k])cnt++;
			if(cnt==1&&graph[i].size()>1){
				edge[i][j]=edge[j][i]=true;
				black[j]=black[i]=true;
				dothing=true;
				break;
			}
			cnt=0;
			for(int k:graph[j])if(!edge[j][k])cnt++;
			if(cnt==1&&graph[j].size()>1){
				edge[i][j]=edge[j][i]=true;
				black[j]=black[i]=true;
				dothing=true;
			}
		}
	}
	for(int i=1;i<=n;i++)if(!black[i])return false;
	return true;
}
void dfs(int x){
	if(ccnt==want&&check())ans=min(ans,ccnt);
	if(x>n||ccnt>=want)return ;
	for(int i=x;i<=n;i++)if(graph[i].size()>1){
		color[i]=true;
		ccnt++;
		dfs(i+1);
		ccnt--;
		color[i]=false;
	}
	return ;
}
int main(){
	int l,r;
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		scanf("%d%d",&l,&r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	ccnt=0;
	ans=n;
	for(int i=1;i<=n;i++){
		want=i;
		dfs(1);
		if(ans==i)break;
	}
	printf("%d\n",ans);
}
