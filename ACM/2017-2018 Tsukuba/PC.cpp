#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
#define maxn 100010
ll h[maxn],pre[maxn],rea[maxn];
int main()
{
	int n,t;scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&h[i]);
		rea[i]=max(h[i],rea[i-1]);
		pre[i]=pre[i-1]+h[i];
	}
	for(int i=1;i<=n;i++)
	{
		if(t<pre[i])puts("1");
		else printf("%lld\n",(t-pre[i])/rea[i]+2);
	}
	return 0;
}
