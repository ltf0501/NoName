bool debug=false;
#include <algorithm>
#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=1e5+10;
struct seg_tree{
    vector<int> v,a;
    void init(int n,int l,int r){
        if(v.size()<=n){
            v.resize(n+1,0);
            a.resize(n+1,0);
        }
        if(l<r){
            int mid=(l+r)>>1;
            init(n*2+1,l,mid);
            init(n*2+2,mid+1,r);
        }
        return ;
    }
    void fix(int n,int l,int r,int pos,int x){
        if(l==r){
            v[n]=x;
            a[n]=1;
        }
        else{
            int mid=(l+r)>>1;
            if(pos>mid)fix(n*2+2,mid+1,r,pos,x);
            else fix(n*2+1,l,mid,pos,x);
            v[n]=v[n*2+1]+v[n*2+2];
            a[n]=a[n*2+1]+a[n*2+2];
        }
    }
    int ask(int n,int l,int r,int L,int R){
        if(L<=l&&r<=R)return v[n];
        else if(l>R||L>r)return 0;
        else{
            int mid=(l+r)>>1;
            return ask(n*2+1,l,mid,L,R)+ask(n*2+2,mid+1,r,L,R);
        }
    }
    int cnt(int n,int l,int r,int L,int R){
        if(L<=l&&r<=R)return a[n];
        else if(l>R||L>r)return 0;
        else{
            int mid=(l+r)>>1;
            return cnt(n*2+1,l,mid,L,R)+cnt(n*2+2,mid+1,r,L,R);
        }
    }
};
int can(int len,int need){
    len-=need;
    return len/2;
}
bool cant(int len,int need){
    return need>len;
}
int main(){
    int n,k,a[N],now=0,pre=0;
    pair<pair<int,int>,int> p[N];
    vector<int> v;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    seg_tree sg;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sg.init(0,1,n);
    for(int i=1;i<=N;i++)if(a[i]!=0)sg.fix(0,1,n,i,a[i]);
    for(int i=0;i<k;i++)scanf("%d%d%d",&p[i].F.F,&p[i].F.S,&p[i].S);
    sort(p,p+k);
    v.resize(n+1);
    for(int i=1;i<=n;i++)if(a[i]==0){
        while(now<k){
            if(p[now].F.F<=i){
                if(cant(p[now].F.S-p[now].F.F+1-sg.cnt(0,1,n,p[now].F.F,p[now].F.S),p[now].S-sg.ask(0,1,n,p[now].F.F,p[now].F.S))){
                    printf("Impossible\n");
                    return 0;
    }
                pq.push({pre+can(p[now].F.S-p[now].F.F+1-sg.cnt(0,1,n,p[now].F.F,p[now].F.S),p[now].S-sg.ask(0,1,n,p[now].F.F,p[now].F.S)),p[now].F.S});
                now++;
            }
            else break;
        }
        while(!pq.empty()){
            if(pq.top().S<i)pq.pop();
            else break;
        }
        if(debug){
            printf("pq.top()=(%d,%d)\n",pq.top().F,pq.top().S);
        }
        if(pq.empty())v[i]=-1;
        else if(pq.top().F-pre>0){
            pre++;
            v[i]=-1;
        }
        else v[i]=1;
    }
    else v[i]=a[i];
    while(now<k){
        if(cant(p[now].F.S-p[now].F.F+1-sg.cnt(0,1,n,p[now].F.F,p[now].F.S),p[now].S-sg.ask(0,1,n,p[now].F.F,p[now].F.S))){
        printf("Impossible\n");
        return 0;
}
        else now++;
    }
    printf("%d",v[1]);
    for(int i=2;i<=n;i++)printf(" %d",v[i]);
    printf("\n");
}
