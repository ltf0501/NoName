#include<bits/stdc++.h>
using namespace std;
#define maxn 105
int main()
{
	int n;scanf("%d",&n);
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		double a,b;cin >> a>>b;
		ans+=a*b;
	}
	printf("%.10f\n",ans);
	return 0;
}
