#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;
#define F first
#define S second
 
const int N=2e2+10;
const int Q=2e4+10;
const int INF=1e9+10;
int min(int a,int b){return a>b?b:a;}
int dis[N][N];
pair<int,int> val[N];
pair<pair<int,int>,pair<int,int>> que[Q];
int ans[Q];
void solve(){
	int n,q,now=1;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&val[i].F);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&dis[i][j]);
	for(int i=1;i<=q;i++)scanf("%d%d%d",&que[i].S.F,&que[i].S.S,&que[i].F.F);
	for(int i=1;i<=q;i++)que[i].F.S=i;
	for(int i=1;i<=n;i++)val[i].S=i;
	sort(val+1,val+n+1);
	sort(que+1,que+q+1);
	for(int k=1;k<=n;k++){
		while(now<=q){
			if(que[now].F.F<val[k].F){
				ans[que[now].F.S]=dis[que[now].S.F][que[now].S.S];
				now++;
			}
			else break;
		}
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][val[k].S]+dis[val[k].S][j]);
	}
	while(now<=q){
		ans[que[now].F.S]=dis[que[now].S.F][que[now].S.S];
		now++;
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return ;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		printf("Case #%d:\n",i);
		solve();
	}
}
