#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;
#define PB push_back
const int N=25;
bitset<N> val,went,used,graph[N];
int n;
bool go(int pos){
    went[pos]=true;
    for(int i=0;i<n;i++)if(!used[i]&&!graph[pos][i]){
        if(went[i]&&(val[i]==val[pos]))return false;
        val[i]=!val[pos];
        if(!went[i])if(!go(i))return false;
    }
    return true;
}
bool ok(){
    went.reset();
    val.reset();
    for(int i=0;i<n;i++)if(!used[i]&&!went[i])if(!go(i))return false;
    return true;
}
bool dfs(bitset<N> can,int pos,int now){
    if(ok())return true;
    if(now>=n/3)return false;
    for(int i=pos;i<n;i++)if(can[i]){
        used[i]=true;
        if(dfs(can&graph[i],i+1,now+1))return true;
        used[i]=false;
    }
    return false;
}
void solve(){
    int l,r,m;
    bitset<N> all;
    scanf("%d%d",&n,&m);
    used.reset();
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)graph[i][j]=true;
    for(int i=0;i<n;i++)all[i]=true;
    while(m--){
        scanf("%d%d",&l,&r);
        graph[l][r]=graph[r][l]=false;
    }
    if(dfs(all,0,0))printf("Y\n");
    else printf("N\n");
    return ;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}
