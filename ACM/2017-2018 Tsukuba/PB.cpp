#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 20
const int INF=1e9;
int x[maxn],y[maxn];
int query[maxn];
int ans,n;
double tmp[maxn];
bool vis[maxn];
double xx(int i,int j)
{
	if(x[i]==x[j])return 1.0*INF;
	return (double)(y[j]-y[i])/(double)(x[j]-x[i]);
}
void check()
{
	for(int i=0;i<n;i+=2)
		tmp[i>>1]=xx(query[i],query[i+1]);
	int res=0;
	for(int i=0;i<n/2;i++)for(int j=i+1;j<n/2;j++)
		if(tmp[i]==tmp[j])res++;
	ans=max(ans,res);
}
void dfs(int num,int st)
{
	if(num==n/2)
	{
		check();
		return ;
	}
	for(int i=st;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			query[num<<1]=i;
			for(int j=i+1;j<=n;j++)if(!vis[j])
			{
				vis[j]=1;
				query[num<<1|1]=j;
				dfs(num+1,i+1);
				vis[j]=0;
			}
			vis[i]=0;
			break ;
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i]],&y[i]);
	dfs(0,1);
	printf("%d\n",ans);
	return 0;
}












