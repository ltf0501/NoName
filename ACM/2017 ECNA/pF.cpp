#include<bits/stdc++.h>
using namespace std;
#define maxn 10010
#define pii pair<int,int>
#define F first
#define S second
vector<int> g[maxn];
int n;
int sz[maxn];
int ans,re;
void dfs(int u,int fa)
{
	int sum=0,tmp_ans=0,tmp_re;
	pii tmp=pii(0,0);
	for(int v : g[u])if(v!=fa)
	{
		dfs(v,u);
		tmp_ans+=sz[u]*sz[v];
		sz[u]+=sz[v];
		if(sz[v]>tmp.F)	tmp.S=tmp.F,tmp.F=sz[v];
		else if(sz[v]>tmp.S) tmp.S=sz[v];	
	}
	int t=n-1-sz[u];
	tmp_ans+=sz[u]*t;
	if(t>tmp.F)	tmp.S=tmp.F,tmp.F=t;
	else if(t>tmp.S) tmp.S=t;
	tmp_re=tmp.F*tmp.S;
	if(tmp_ans>ans)
	{
		ans=tmp_ans,re=tmp_re;
	}
	else if(tmp_ans==ans)
	{
		if(tmp_re<re)re=tmp_re;
	}
	sz[u]++;
}
int main()
{
	scanf("%d",&n);
	n++;
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		x++,y++;
		g[x].push_back(y),g[y].push_back(x);
	}
	dfs(1,-1);
	printf("%d %d\n",ans,ans-re);
	return 0;
}
