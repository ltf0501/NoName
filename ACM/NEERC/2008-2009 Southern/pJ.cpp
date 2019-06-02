#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
#include <math.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define double long double
const int INF=1e6+10;
double u;
double value(double lim,double v,double w){
	double l=w/u,r=INF,mid;
	while(r-l>1e-10){
		mid=(l+r)/2;
		if(mid*u*u>(lim-v)*sqrt(mid*mid*u*u-w*w))l=mid;
		else r=mid;
	}
	return l;
}
double f(double t,double v,double w){
	double ans=sqrt(t*t*u*u-w*w)+v*t;
	return ans;
}
int main(){
	int n,t,w,temp,tot=0;
	double ans=0,l=0,r=INF,mid,tt;
	vector<pair<int,int>> v;
	map<int,int> m;
	map<int,double> mans;
	int u_;
	scanf("%d%d%d",&n,&u_,&t);
	u = u_;
	for(int i=0;i<n;i++){
		scanf("%d%d",&w,&temp);
		v.PB({w,temp});
		m[temp]+=w;
		tot+=w;
	}
	if(t*u<tot){
		printf("-1\n");
		return 0;
	}
	while(r-l>1e-10){
		mid=(l+r)/2;
		tt=0;
		for(pair<int,int> i:m)tt+=value(mid,i.F,i.S);
		if(tt>t)l=mid;
		else r=mid;	
	}
	for(pair<int,int> i:m){
		mans[i.F]=value(r,i.F,i.S);
		ans+=f(mans[i.F],i.F,i.S);
	}
	ans=sqrt(ans*ans+tot*tot);
#undef double
#define db double
	printf("%.20lf\n%.20lf",db(ans),db(mans[v[0].S]/m[v[0].S]*v[0].F));
	for(int i=1;i<n;i++)printf(" %.20lf",db(mans[v[i].S]/m[v[i].S]*v[i].F));
	printf("\n");
}
