#include <stdio.h>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=2e2+10;
const double INF=1e16+10;
double min(double a,double b){return a>b?b:a;}
double dist(pair<double,double> a,pair<double,double> b){
    double x=a.F-b.F,y=a.S-b.S;
    return sqrt(x*x+y*y);
}
bool between(pair<double,double> a,pair<double,double> b,pair<double,double> c){
    
    if(!((a.F<=b.F&&b.F<=c.F)||(a.F>=b.F&&b.F>=c.F)))return false;
    if(!((a.S<=b.S&&b.S<=c.S)||(a.S>=b.S&&b.S>=c.S)))return false;
    return true;
}
pair<double,double> lineintersect(double A1,double B1,double C1,double A2,double B2,double C2){
    double x,y,det;
    x=(C1*B2-C2*B1);
    y=(A1*C2-A2*C1);
    det=(A1*B2-A2*B1);
    return {x/det,y/det};
}
pair<double,double> intersect(pair<double,double> a,pair<double,double> b,pair<double,double> c){
    double A=b.S-c.S,B=c.F-b.F,C,rA,rB;
    C=A*b.F+B*b.S;
    rA=B;
    rB=-A;
    return lineintersect(rA,rB,rA*a.F+rB*a.S,A,B,C); 
}
double distance(vector<pair<double,double>> &l,vector<pair<double,double>> &r){
    double ans=INF;
    pair<double,double> left,right,now;
    for(int i=0;i<l.size();i++)for(int j=0;j<r.size();j++)ans=min(ans,dist(l[i],r[j]));
    for(int i=0;i<l.size();i++){
        for(int j=1;j<r.size();j++){
            left=r[j-1];
            right=r[j];
            now=intersect(l[i],left,right);
            if(between(left,now,right))ans=min(ans,dist(l[i],now));
        }
        left=r[0];
        right=r.back();
        now=intersect(l[i],left,right);
        if(between(left,now,right))ans=min(ans,dist(l[i],now));
    }
    for(int i=0;i<r.size();i++){
        for(int j=1;j<l.size();j++){
            left=l[j-1];
            right=l[j];
            now=intersect(r[i],left,right);
            if(between(left,now,right))ans=min(ans,dist(r[i],now));
        }
        left=l[0];
        right=l.back();
        now=intersect(r[i],left,right);
        if(between(left,now,right))ans=min(ans,dist(r[i],now));
    }
    return ans;
}
int main(){
    int n,k,s=0,t;
    double dis[N][N],w;
    pair<double,double> temp;
    vector<pair<double,double>> v[N];
    scanf("%lf%d",&w,&n);
    t=n+1;
    for(int i=1;i<=n;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%lf%lf",&temp.F,&temp.S);
            v[i].PB(temp);
        }
    }
    for(int i=s;i<=t;i++)for(int j=s;j<=t;j++)dis[i][j]=INF;
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)dis[i][j]=dis[j][i]=distance(v[i],v[j]);
    for(int i=1;i<=n;i++){
        dis[s][i]=INF;
        dis[i][t]=INF;
        for(pair<double,double> j:v[i])dis[s][i]=min(dis[s][i],j.F);
        for(pair<double,double> j:v[i])dis[i][t]=min(dis[i][t],w-j.F);
    }
    for(int k=s;k<=t;k++)for(int i=s;i<=t;i++)for(int j=s;j<=t;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    printf("%.9lf\n",min(w,dis[s][t]));
}
