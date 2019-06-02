#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
#define ll long long 
vector<int> v;
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<k;i++)
	{
		int x;scanf("%d",&x);
		v.push_back(x);
	}
	v.push_back(n+1);
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		int k=lower_bound(v.begin(),v.end(),i)-v.begin();
		int s=v[k];
		ans+=n-s+1;
	}
	printf("%lld\n",ans);
	return 0;
}
