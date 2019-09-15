#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=5e3+10;
int myabs(int n){return n>0?n:-n;}
int max(int a,int b){return a>b?a:b;}
vector<int> graph[N];
int dp[N];
int dis(int pos){
    if(dp[pos]>=0)return dp[pos];
    dp[pos]=0;
    for(int i:graph[pos])dp[pos]=max(dp[pos],dis(i)+1);
    return dp[pos];
}
int main(){
    int ans=0,n,a[N],w;
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j)if(a[j]>a[i]&&myabs(j-i)<=w)graph[i].PB(j);
    for(int i=1;i<=n;i++)dp[i]=-1;
    for(int i=1;i<=n;i++)if(graph[i].empty())dp[i]=0;
    for(int i=1;i<=n;i++)ans=max(ans,dis(i));
    printf("%d\n",ans);
}
