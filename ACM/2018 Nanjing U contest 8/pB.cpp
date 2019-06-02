#include <stdio.h>
#include <math.h>
const int INF=1e9+10;
double max(double a,double b){return a>b?a:b;}
double min(double a,double b){return a>b?b:a;}
double hx(double c,double b,double a,double x1,double y1,double x2,double y2,double w,double cos,double sin){
	x2=cos*x1+sin*y1;
	y2=-sin*x1+cos*y1;
	x2*=(b/c);
	y2*=(b/c);
	if(x2+1e-9<0||x2-1e-9>w)return INF;
	return max(max(fabs(y2),fabs(y2-y1)),fabs(y1));
}
double height(int w,double c,double b,double a){
	double sin, x1,y1,x2,y2,cos,temp;
	if(c>=w){
		x1=w;
		y1=sqrt(c*c-w*w);
	}
	else{
		x1=c;
		y1=0;
	}
	cos=(b*b+c*c-a*a)/(2*b*c);
	sin=sqrt(1-cos*cos);
	x2=cos*x1-sin*y1;
	y2=sin*x1+cos*y1;
	x2*=(b/c);
	y2*=(b/c);
	temp=hx(c,b,a,x1,y1,x2,y2,w,cos,sin);
	//printf("a=%Lf b=%Lf c=%Lf ans=%Lf\n",a,b,c,fabs(y2));
	if(x2+1e-9<0||x2-1e-9>w)return temp;
	return min(temp,max(max(fabs(y2),fabs(y2-y1)),fabs(y1)));
}
double dis(int x1,int y1,int x2,int y2){
	int x=x1-x2,y=y1-y2;
	return sqrt(x*x+y*y);
}
int main(){
	int t,x1,x2,x3,y1,y2,y3,w;
	double ans,a,b,c;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&w);
		ans=INF;
		a=dis(x1,y1,x2,y2);
		b=dis(x2,y2,x3,y3);
		c=dis(x3,y3,x1,y1);
		ans=min(ans,height(w,a,b,c));
		ans=min(ans,height(w,a,c,b));
		ans=min(ans,height(w,b,a,c));
		ans=min(ans,height(w,b,c,a));
		ans=min(ans,height(w,c,a,b));
		ans=min(ans,height(w,c,b,a));
		if(ans==INF)printf("impossible\n");
		else printf("%.9lf\n",ans);
	}
}
