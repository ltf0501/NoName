#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
vector<int> g[maxn];
#define pii pair<int,int>
#define F first
#define S second
int n,q;
int in[maxn],out[maxn],dfs_clock;
int tour[maxn];
int cost[maxn];
void dfs(int u)
{
	in[u]=++dfs_clock;
	tour[dfs_clock]=u;
	for(int v : g[u])
	{
		dfs(v);
	}	
	out[u]=dfs_clock;
}
int mx[maxn<<2],mn[maxn<<2],tg[maxn<<2];
void push_up(int o)
{
	mx[o]=max(mx[o<<1],mx[o<<1|1]);	
	mn[o]=min(mn[o<<1],mn[o<<1|1]);
}
void push_down(int o)
{
	if(!tg[o])return ;
	mx[o<<1]+=tg[o],mx[o<<1|1]+=tg[o];
	mn[o<<1]+=tg[o],mn[o<<1|1]+=tg[o];
	tg[o<<1]+=tg[o],tg[o<<1|1]+=tg[o];
	tg[o]=0;
}
void build(int l,int r,int o)
{
	tg[o]=0;
	if(l==r)
	{
		mx[o]=mn[o]=cost[tour[l]];
		return ;
	}
	int m=(l+r)>>1;
	build(l,m,o<<1),build(m+1,r,o<<1|1);
	push_up(o);
}
void update(int l,int r,int o,int ql,int qr,int k)
{
	if(ql<=l && r<=qr)
	{
		mx[o]+=k,mn[o]+=k,tg[o]+=k;
		return ;
	}
	push_down(o);
	int m=(l+r)>>1;
	if(ql<=m)update(l,m,o<<1,ql,qr,k);
	if(qr>m)update(m+1,r,o<<1|1,ql,qr,k);
	push_up(o);
}
pii query(int l,int r,int o,int ql,int qr)
{
	if(ql<=l && r<=qr)return pii(mx[o],mn[o]);
	push_down(o);
	int m=(l+r)>>1;
	if(qr<=m)return query(l,m,o<<1,ql,qr);
	if(ql>m)return query(m+1,r,o<<1|1,ql,qr);
	pii le=query(l,m,o<<1,ql,qr);
	pii ri=query(m+1,r,o<<1|1,ql,qr);
	return pii(max(le.F,ri.F),min(le.S,ri.S));
}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=2;i<=n;i++)
		{
			int p;scanf("%d",&p);
			g[p].push_back(i);
		}
		for(int i=1;i<=n;i++)scanf("%d",&cost[i]);
		dfs_clock=0;
		dfs(1);
		build(1,n,1);
		scanf("%d",&q);
		while(q--)
		{
			char c[2];scanf("%s",c);
			if(c[0]=='R')
			{
				int u,k;scanf("%d%d",&u,&k);
				update(1,n,1,in[u],out[u],k);
			}
			else
			{
				int u;scanf("%d",&u);
				pii ans=query(1,n,1,in[u],out[u]);
				printf("%d\n",ans.F-ans.S);
			}
		}
	}

	return 0;
}
  
