#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=5e3+10;
int f[N][N];
vector<int> v;
int dp(int n,int m){
	if(m<0||n<0)return 0;
	if(m>n)return 0;
	if(m==0&&n==0)return 1;
	if(m==0||n==0)return 0;
	if(f[n][m]!=-1)return f[n][m];
	int ans=0;
	for(int i:v)if(m>=i)if(dp(n-m,m-i)==1){
		ans=1;
		break;
	}
	return f[n][m]=ans;
}
int main(){
	int n,m,t,temp,ans;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		v.clear();
		while(m--){
			scanf("%d",&temp);
			v.PB(temp);
		}
		for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)f[i][j]=-1;
		ans=-1;
		for(int i=n;i>=0;i--)if(dp(n,i)==1){
			ans=i;
			break;
		}
		printf("%d\n",ans);
	}
}
