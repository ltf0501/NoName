bool debug=false;
#include <stdio.h>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=10;
const int M=1e2+10;
int dp[1<<N][M][M][2];
// usd str tox
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a>b?b:a;}
void solve(){
	int ans=0,k,m,n,e[N],p[N],tot;
	scanf("%d%d%d",&k,&m,&n);
	for(int i=0;i<n;i++)scanf("%d",&e[i]);
	for(int i=0;i<n;i++)scanf("%d",&p[i]);
	tot=1<<n;
	for(int i=0;i<tot;i++)for(int j=0;j<=100;j++)for(int x=0;x<=100;x++)dp[i][j][x][0]=dp[i][j][x][1]=0;
	for(int i=0;i<tot;i++)for(int j=100;j>=0;j--)for(int x=100;x>=0;x--){
		ans=max(ans,dp[i][j][x][0]);
		ans=max(ans,dp[i][j][x][1]);
		if(j>k)dp[i][j-k][max(x-m,0)][0]=max(dp[i][j-k][max(x-m,0)][0],max(dp[i][j][x][1],dp[i][j][x][0])+1);
		for(int y=0;y<n;y++)if(!(i&(1<<y))){
			if(x+p[y]<100)dp[i|(1<<y)][min(j+e[y],100)][x+p[y]][1]=max(dp[i|(1<<y)][min(j+e[y],100)][x+p[y]][1],dp[i][j][x][0]);
		}
	}
	printf("%d\n",ans);
	return ;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)solve();
}
