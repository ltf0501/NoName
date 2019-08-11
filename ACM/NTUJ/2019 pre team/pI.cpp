bool debug=false;
#include <stdio.h>
#include <vector>
#include <set>
#include <utility>
using namespace std;
const int N=1e5+10;
int ans=-1;
bool same=true;
int p[N];
int find(int n){return p[n]==n?n:p[n]=find(p[n]);}
void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
    return ;
}
bool check(int n,int m){
    set<pair<int,int>> ma;
    int l,r,tans=1;
    bool f=true;    
    for(int i=1;i<=n;i++)p[i]=i;
    for(int i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        if(l>r)swap(l,r);
        if(l==r)f=false;
        else if(ma.find(make_pair(l,r))!=ma.end())f=false;
        else{
            ma.insert(make_pair(l,r));
            l=find(l);
            r=find(r);
            if(l!=r)p[l]=r;
        }
    }
    for(int i=2;i<=n;i++)if(find(i)!=find(1))tans=0;
    if(ans==-1)ans=tans;
    else if(ans!=tans)same=false;
    return f;
}
int main(){
    int n,tn,tm,m,t;
    bool hn=false,hm=false,ok=true;
    scanf("%d%d%d",&n,&m,&t);
    for(int i=0;i<t;i++){
        scanf("%d%d",&tn,&tm);
        if(tn==n)hn=true;
        if(tm==m)hm=true;
        ok&=check(tn,tm);
    }
    if(debug){
        printf("hn==%d\n",hn?1:0);
        printf("hm==%d\n",hm?1:0);
        printf("same==%d\n",same?1:0);
        printf("ok==%d\n",ok?1:0);
    }
    if(!hn||!hm||same||!ok)printf("India\n");
    else printf("Normal\n");
}
