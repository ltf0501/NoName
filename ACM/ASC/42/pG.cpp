bool debug=false;
#include <assert.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N=1e5+10;
int d[N],n,cost[N],in[N];
bool ok[N];
vector<int> ans,graph[N];
bool check(int val){
	if(debug)printf("val=%d\n",val);
	queue<int> q;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	int now=n,nxt,temp;
	ans.clear();
	for(int i=1;i<=n;i++)in[i]=cost[i];
	for(int i=1;i<=n;i++)ok[i]=false;
	for(int i=1;i<=n;i++)if(in[i]==0)ok[i]=true;
	for(int i=1;i<=n;i++)pq.push({-d[i],i});
	while(!pq.empty()){
		if(pq.top().F+now<=val){
			nxt=pq.top().S;
			pq.pop();
			if(debug)printf("2 now=%d %d\n",now,nxt);
			if(ok[nxt])q.push(nxt);
			else ok[nxt]=true;
		}
		else break;
	}
	while(!q.empty()){
		temp=q.front();
		q.pop();
		ans.PB(temp);
		for(int i:graph[temp]){
			in[i]--;
			if(in[i]==0){
				if(debug)printf("1 %d\n",i);
				if(ok[i])q.push(i);
				else ok[i]=true;
			}
		}
		now--;
		while(!pq.empty()){
			if(pq.top().F+now<=val){
				nxt=pq.top().S;
				pq.pop();
				if(debug)printf("2 now=%d %d\n",now,nxt);
				if(ok[nxt])q.push(nxt);
				else ok[nxt]=true;
			}
			else break;
		}
	}
	return now==0;
}
void solve(){
	int m,l,r,mid;
	for(int i=1;i<=n;i++)scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)cost[i]=0;
	for(int i=1;i<=n;i++)graph[i].clear();
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&l,&r);
		graph[r].PB(l);
		cost[l]++;
	}
	l=-1;
	r=n;
	while(r-l>1){
		mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	check(r);
	reverse(ans.begin(),ans.end());
	printf("%d\n%d",r,ans[0]);
	for(int i=1;i<n;i++)printf(" %d",ans[i]);
	printf("\n");
	for(int i=0;i<n;i++)assert(r>i-d[ans[i]]);
}
int main(){
	freopen("grand.in","r",stdin);
	freopen("grand.out","w",stdout);
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		else solve();
	}
}
