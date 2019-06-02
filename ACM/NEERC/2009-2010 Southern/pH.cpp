#include<bits/stdc++.h>
using namespace std;
int s,m,p;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d%d",&s,&m,&p);
	double x;
	if(p==0)
	{
		x=(1.0*s)/(1.0*m);
	}
	else 
	{
	double k=pow(1+1.0*p/100.0,m);
	 x=(1.0*p*s*k)/(100.0*(k-1.0));
	}
	printf("%.9f\n",x);
	return 0;
}
