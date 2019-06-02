#include<bits/stdc++.h>
using namespace std;
#define maxn 22
int n,k;
string ans;
int trans(int x)
{
	vector<int> v;
	while(x)
	{
		if(x&1)v.push_back(1);
		else v.push_back(0);
		x>>=1;
	}
	int m=(int)v.size();
	int res=1<<(m-1);
	for(int i=m-2;i>=0;i--)
		if(v[i]^v[i+1])res+=(1<<i);
	return res;
}
void cal(int pre,int now)
{
	int cnt=0;
	while(1)
	{
		if((pre&1)^(now&1))
		{
			int a=pre&1;
			int b=(pre>>1)&1;
			int c=(now>>1)&1;
			if(a==0)
			{
				if(b==c)ans+=(string("+")+to_string(cnt+1));
				else ans+=(string("--")+to_string(cnt+1+1));	
			}
			else 
			{
				if(b==c)ans+=(string("-")+to_string(cnt+1));
				else ans+=(string("++")+to_string(cnt+1));
			}
			return ;
		}
		pre>>=1, now>>=1, cnt++;
	}
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	ans+="+1";
	int pre=1;
	/*
	for(int i=2;i<(1<<n);i++)
		printf("%d: %d\n",i,trans(i));
	*/
	for(int i=2;i<(1<<n);i++)
	{
		int now=trans(i);
		if(__builtin_popcount(now)>k) continue;
		cal(pre, now);
		pre=now;
	}
	ans+=(string("-")+to_string(n));
	cout << ans <<'\n';
	return 0;
}
