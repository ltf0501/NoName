#include <algorithm>
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=1e5+10;
int dp[N][2],p[N],sz[N];
bool ok[N],went[N];
vector<int>graph[N];
queue<int> q;
void f(int pos){
	if(went[pos])return ;
	went[pos]=ok[pos]=true;
	sz[pos]=1;
	for(int i:graph[pos])f(i);
	dp[pos][0]=0;
	for(int i:graph[pos])sz[pos]+=sz[i];
	for(int i:graph[pos])dp[pos][0]+=dp[i][1];
	dp[pos][1]=dp[pos][0];
	for(int i:graph[pos])if(dp[i][0]==dp[i][1]){
		dp[pos][1]++;
		ok[pos]=ok[i]=false;
		break;
	}
	return ;
}
void dfs(int pos){
	for(int i:graph[pos])dfs(i);
	if(ok[pos])q.push(pos);
	return ;
}
int main(){	
#ifdef ONLINE_JUDGE
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout); 
#endif
	int n,cnt=0;
	vector<pair<int,int>> v;
	scanf("%d",&n);
	for(int i=2;i<=n;i++)scanf("%d",&p[i]);
	for(int i=2;i<=n;i++)graph[p[i]].PB(i);
	for(int i=1;i<=n;i++)went[i]=false;
	for(int i=1;i<=n;i++)if(!went[i])f(i);
	cnt+=dp[1][1];
	dfs(1);
	for(int i=2;i<=n;i++)if(p[i]==0){
		if(!ok[i]){
			cnt+=dp[i][1];
			p[i]=1;
			dfs(i);
		}
	}
	for(int i=2;i<=n;i++)if(p[i]==0)v.PB({dp[i][1]*2-sz[i],i});
	sort(v.begin(),v.end());
	for(pair<int,int> i:v){
		if(q.empty()||!ok[i.S]){
			cnt+=dp[i.S][1];
			p[i.S]=1;
		}
		else {
			cnt+=dp[i.S][0]+1;
			p[i.S]=q.front();
			ok[i.S]=false;
			q.pop();
		}
		dfs(i.S);
	}
	printf("%d\n%d",cnt,p[2]);
	for(int i=3;i<=n;i++)printf(" %d",p[i]);
	printf("\n");
}
