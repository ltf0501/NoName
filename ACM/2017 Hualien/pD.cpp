bool debug=false;
#include <stdio.h>
const int N=2e2+10;
const int INF=1e8+10;
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}
void solve(int n,int m){
    int top=0,l,r,dis[N][N],cnt[N];
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)dis[i][j]=INF;
    for(int i=0;i<m;i++){
        scanf("%d%d",&l,&r);
        dis[l][r]=dis[r][l]=1;
    }
    for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=n;i++)cnt[i]=0;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(i!=j)if(dis[i][j]<INF){
        cnt[dis[i][j]]++;
        top=max(top,dis[i][j]);
    }
    for(int i=1;i<=top;i++)printf("%d %d\n",i,cnt[i]);
    return ;
}
int main(){
    int n,e;
    while(true){
        scanf("%d",&n);
        if(n==0)break;
        scanf("%d",&e);
        solve(n,e);
    }
}
