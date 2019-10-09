#include <stdio.h>
const int MOD=1e9+7;
const int N=6e2+10;
long long int f[N],inf[N];
long long int pow(long long int a,long long int b){
	long long int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return ans;
}
long long int inv(long long int n){return pow(n,MOD-2);}
void pre(){
	f[0]=1;
	for(int i=1;i<N;i++)f[i]=(f[i-1]*i)%MOD;
	inf[N-1]=inv(f[N-1]);
	for(int i=N-2;i>=0;i--)inf[i]=(inf[i+1]*(i+1))%MOD;
	return ;
}
long long int C(long long int a,long long int b){
	if(a<b)return 0;
	return (f[a]*((inf[b]*inf[a-b])%MOD))%MOD;
}
long long int val(long long int i,long long int x,long long int s,long long int a){
	long long int ans=C(s+a-x,a-1)-C(i+a-x-1,a-1);
	ans%=MOD;
	if(ans<0)ans+=MOD;
	return ans;
}
int main(){
	freopen("monotonic.in","r",stdin);
	freopen("monotonic.out","w",stdout);
	int n,k,a[N],s[N];
	long long int ans=0,dp[N][N];
	scanf("%d%d",&n,&k);
	pre();
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=0;
	for(int i=1;i<=k;i++)scanf("%d",&a[i]);
	s[0]=0;
	for(int i=1;i<=k;i++)s[i]=s[i-1]+a[i];
	dp[1][1]=1;
	for(int i=2;i<=k;i++){
		if(a[i]==1){
			for(int x=1;x<=s[i];x++){
				for(int j=1;j<x;j++)dp[i][x]+=dp[i-1][j];
				dp[i][x]%=MOD;
			}
		}
		else{
			for(int x=1;x<s[i];x++){
				for(int j=1;j<=s[i-1];j++){
					dp[i][x]=(dp[i][x]+((val(j,x,s[i-1],a[i])*dp[i-1][j])%MOD))%MOD;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)ans+=dp[k][i];
	printf("%lld\n",ans%MOD);
}
