#include <iostream>
#include <math.h>
#include <map>
#include <iomanip>
using namespace std;
#define F first
#define S second
const int N=1e2+10;
double dis(double x1,double y1,double z1,double x2,double y2,double z2){
	x1-=x2;
	y1-=y2;
	z1-=z2;
	return sqrt(x1*x1+y1*y1+z1*z1);
}
double min(double a,double b){return a>b?b:a;}
const double INF=1e9+10;
int main(){
	int t,p,a,b,w,q;
	double x[N],y[N],z[N];
	double v[N][N],d[N][N];
	map<string,int> m;
	string s,temp;
	//cout<<(int)round(0.5)<<endl;
	cin>>t;
	for(int i=1;i<=t;i++){
		cout<<"Case "<<i<<":"<<endl;
		cin>>p;
		m.clear();
		for(int i=0;i<p;i++){
			cin>>s>>x[i]>>y[i]>>z[i];
			m.insert({s,i});
		}
		cin>>w;
		for(int i=0;i<p;i++)for(int j=0;j<p;j++)if(i==j)d[i][j]=v[i][j]=0;
		else d[i][j]=v[i][j]=dis(x[i],y[i],z[i],x[j],y[j],z[j]);
		while(w--){
			cin>>s>>temp;
			a=m[s];
			b=m[temp];
			d[a][b]=v[a][b]=0;
		}
		for(int k=0;k<p;k++)for(int i=0;i<p;i++)for(int j=0;j<p;j++)if(i!=j)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		cin>>q;
		while(q--){
			cin>>s>>temp;
			a=m[s];
			b=m[temp];
			cout<<"The distance from "<<s<<" to "<<temp<<" is "<<(int)round(d[a][b])<<" parsecs."<<endl;

		}
	}
}

