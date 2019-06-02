#include <stdio.h>
#include <math.h>
int main(){
	freopen("glorious.in","r",stdin);
	int t,n;
	double ans;
	double r;
	int k;
	const double pi=acos(-1);
	scanf("%d",&t);
	for(int o=1;o<=t;o++){
		printf("Case %d: ",o);
		scanf("%d%lf%d",&n,&r,&k);
		ans=(k*r*r*tan(pi/k))-pi*r*r;
		double c=cos(pi/k);
		ans=ans*(1-1.0/pow(c,2*n))/(1-1.0/pow(c,2));
		printf("%.5f\n",ans);
	}
}
