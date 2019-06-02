#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e7;
ll a,b,c;
ll f(ll x)
{
	return (a*x+x%b)%c;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%lld%lld%lld",&a,&b,&c);
	ll x1=1,x2=1;
	int N=0;
	do
	{
		x1=f(x1), x2=f(f(x2));
		N++;
	}while(x1!=x2 && N<=maxn);
	if(x1!=x2)return 0*puts("-1");
	int cyc=0;
	do
	{
		x1=f(x1);
		cyc++;
	}while(x1!=x2);
	x2=1;
	int st=0;
	while(x1!=x2)
	{
		x1=f(x1), x2=f(x2);
		st++;
	}
	if(st+cyc>maxn)puts("-1");
	printf("%d\n",st+cyc);
	return 0;
}
