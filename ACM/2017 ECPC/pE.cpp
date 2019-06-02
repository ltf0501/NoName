#include <stdio.h>
#include <vector>
#include <utility>
#include <bitset>
#include <map>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N=1e5+10;
vector<pair<int,int>>graph[N];
bitset<N> two,one,went;
long long int ans;
int pp[N],p[N];
long long int val[N];
vector<int> P;
int find(int n){return p[n]==n?n:p[n]=find(p[n]);}
void pre(){
	one.reset();
	two.reset();
	for(int i=2;i<N;i++)
	{
		if(!pp[i])pp[i]=i,P.push_back(i);
		for(int j=0;j<(int)P.size() && 1ll*i*P[j]<N;j++)
		{
			pp[i*P[j]]=P[j];
			if(i%P[j]==0)break;
		}
	}
	for(int i=2;i<N;i++)
	{
		int cur=i;
		int cnt=0;
		while(cur!=1)
		{
			int tmp=0;
			int d=pp[cur];
			while(cur%d==0)cur/=d,tmp++;
			if(tmp>1){cnt=100;break;}	
			cnt++;
		}
		if(cnt==1)one[i]=1;
		if(cnt==2)two[i]=1;
	}
	return ;
}
void dfs(int now,int p,int pv){
	long long int cnt=0;
	map<int,long long int> m;
	if(p!=0&&one[pv]){
		cnt+=val[p];
		m[pv]=val[p];
	}
	went[now]=true;
	for(pair<int,int> j:graph[now])if(!went[find(j.F)]){if(two[j.S]){
		ans+=val[now]*val[find(j.F)];
	}
	else if(one[j.S]){
		cnt+=val[find(j.F)];
		m[j.S]+=val[find(j.F)];
		ans+=val[find(j.F)]*(cnt-m[j.S]);
	}
	dfs(find(j.F),now,j.S);
	}
	//printf("now=%d p=%d pv=%d ans=%lld\n",now,p,pv,ans);
	return ;
}
int main(){
	freopen("evaluations.in","r",stdin);
	int t,n,l,r,k;
	scanf("%d",&t);
	pre();
	for(int o=1;o<=t;o++){
		scanf("%d",&n);
		ans=0;
		for(int i=1;i<=n;i++)graph[i].clear(),val[i]=1,p[i]=i;
		for(int i=1;i<n;i++){
			scanf("%d%d%d",&l,&r,&k);
			if(k==1)p[find(l)]=find(r);
			else{
				graph[l].PB({r,k});
				graph[r].PB({l,k});
			}	
		}
		for(int i=1;i<=n;i++)if(p[i]!=i){
			val[find(i)]++;
			for(pair<int,int> j:graph[i])graph[find(i)].PB({find(j.F),j.S});
		}
		//for(int i=1;i<=n;i++){
		//	printf("::%d::val=%lld\n",i,val[i]);
		//	for(pair<int,int> j:graph[i])printf("%d %d\n",j.F,j.S);
		//}
		went.reset();
		dfs(find(1),0,0);
		printf("Case %d: %lld\n",o,ans);
	}
}
