#include <stdio.h>
#include <vector>
#include <bitset>
#include <utility>
using namespace std;
const int N=1e5+10;
#define F first
#define S second
#define PB push_back
vector<pair<int,pair<int,int>>> graph[N];
pair<int,int> pos[N];
bitset<N> went;
void dfs(int n){
	went[n]=true;
	for(pair<int,pair<int,int>> i:graph[n])if(!went[i.F]){
		pos[i.F]={pos[n].F+i.S.F,pos[n].S+i.S.S};
		dfs(i.F);
	}
	return ;
}
int main(){
	int l,r,x,y,n,m;
	scanf("%d%d",&n,&m);
	went.reset();
	while(m--){
		scanf("%d%d%d%d",&l,&r,&x,&y);
		graph[l].PB({r,{x,y}});
		graph[r].PB({l,{-x,-y}});
	}
	for(int i=1;i<=n;i++)if(!went[i]){
		pos[i]={0,0};
		dfs(i);
	}
	for(int i=1;i<=n;i++)printf("%d %d\n",pos[i].F,pos[i].S);
}
