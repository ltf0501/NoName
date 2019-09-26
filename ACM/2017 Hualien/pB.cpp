#include <stdio.h>
const int N=3e2+10;
const int INF=1e6+10;
int max(int a,int b){return a>b?a:b;}
void solve(){
    int n,tot,a[N][N],ans=0,l,r,v;
    scanf("%d",&n);
    tot=((n-1)*n)/2;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=-INF;
    while(tot--){
        scanf("%d%d%d",&l,&r,&v);
        a[l][r]=a[r][l]=v;
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j)for(int k=1;k<=n;k++)if(i!=k&&j!=k)ans=max(ans,a[i][j]+a[j][k]+a[k][i]);
    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
    
}
