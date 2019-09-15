#include <stdio.h>
#include <vector>
#include <stack>
#include <bitset>
using namespace std;
#define PB push_back
const int N=2e2+10;
int tt,ans,dep[N],top[N];
stack<int> s;
vector<int> graph[N];
bitset<N> went,ins;
void dfs(int n){
    ins[n]=went[n]=true;
    dep[n]=top[n]=++tt;
    s.push(n);
    for(int i:graph[n]){
        if(!went[i])dfs(i);
        if(ins[i])top[n]=min(top[i],top[n]);
    }
    if(dep[n]==top[n]){
        while(s.top()!=n){
            ins[s.top()]=false;
            s.pop();
        }
        ins[n]=false;
        s.pop();
        ans++;
    }
    return ;
}
void solve(){
    int n,m,l,r;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)graph[i].clear();
    while(m--){
        scanf("%d%d",&l,&r);
        graph[l].PB(r);
    }
    ans=0;
    went.reset();
    for(int i=0;i<n;i++)if(!went[i])dfs(i);
    printf("%d\n",ans);
    return ;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}
