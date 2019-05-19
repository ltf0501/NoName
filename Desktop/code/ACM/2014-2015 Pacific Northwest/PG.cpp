nclude<bits/stdc++.h>
using namespace std;
#define maxn 105
int dp[maxn][maxn][2];
int a[maxn];
int n,p;
bool dfs(int l,int r,int k)
{
	if(dp[l][r][k]!=-1)return dp[l][r][k];
	bool cur=1;
	if(a[l]>a[l+1])cur&=dfs(l+1,r,k);
	if(a[r]>a[r-1])cur&=dfs(l,r-1,k);
	for(int i=l+1;i<p;i++)if(a[i]>a[i-1] && a[i]>a[i+1])
		cur&=dfs(i+1,r,k^((i-l)&1));
	for(int i=p+1;i<r;i++)if(a[i]>a[i-1] && a[i]>a[i+1])
		cur&=dfs(l,i-1,k^((r-i)&1));
	if(k)cur&=dfs(l,r,0);
	return dp[l][r][k]=cur^1;
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		memset(dp,-1,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			if(a[i]==1){p=i;break;}
		dp[p][p][0]=dp[p][p][1]=1;
		puts(dfs(1,n,0) ? "Alice" : "Bob");
		/*
		for(int len=0;len<n;len++)for(int i=1;i+len<=n;i++)for(int k=0;k<2;k++)
			printf("dp[%d][%d][%d] = %d\n",i,i+len,k,dp[i][i+len][k]);		
		*/
	}
	return 0;
}
