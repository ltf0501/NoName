#include <stdio.h>
const int N=2e5+10;
bool ok;
int l1[N],r1[N],l2[N],r2[N],ans,al[N],ar[N];
int dfs(int posl,int posr){
	int now=++ans;
	if(l1[posl]!=0&&l2[posr]!=0)al[now]=dfs(l1[posl],l2[posr]);
	else if(l1[posl]==0&&l2[posr]==0)al[now]=0;
	else al[now]=0,ok=false;
	if(r1[posl]!=0&&r2[posr]!=0){
		if(ok)ar[now]=dfs(r1[posl],r2[posr]);
		else ar[now]=++ans, al[ans] = ar[ans] = 0;
	}
	else if(r1[posl]==0&&r2[posr]==0)ar[now]=0;
	else ar[now]=0,ok=false;
	return now;
}
void solve(int n){
	int m;
	for(int i=1;i<=n;i++)scanf("%d%d",&l1[i],&r1[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&l2[i],&r2[i]);
	ans=0;
	ok=true;
	dfs(1,1);
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d %d\n",al[i],ar[i]);
	return ;
}
int main(){
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
	int n;
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		solve(n);
	}
}
