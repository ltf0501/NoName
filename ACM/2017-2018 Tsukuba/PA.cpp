#include<cstdio>
#define ll long long 
ll dp[105][2];

int main()
{
	int n,k;scanf("%d%d",&n,&k);
	dp[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		dp[i][0]=dp[i-1][1];
		dp[i][1]=dp[i-1][0];
		if(i>=k)dp[i][1]+=dp[i-k][0];
	}
	ll ans=0;
	for(int i=1;i<=n;i++)ans+=dp[i][1];
	printf("%lld\n",ans);
	return 0;
}
