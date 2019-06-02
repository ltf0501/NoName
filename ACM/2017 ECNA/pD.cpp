#include<bits/stdc++.h>
using namespace std;
int cal(string s)
{
	int i=(s[0]=='-');
	bool flag=(s[0]=='-');
	int len=s.length();
	int res=0;
	for(;i<len;i++)
	{
		res=res*10+(s[i]-'0');
	}
	if(flag)res=-res;
	return res;
}
int main()
{
	int n,k;scanf("%d%d",&n,&k);
	int now=0;
	stack<int> s;
	for(int i=0;i<k;i++)
	{
		string c;
		cin >> c;
		if(c[0]=='u')
		{
			int x;scanf("%d",&x);
			while(x--)s.pop();
		}
		else 
		{
			int x=cal(c);
			x%=n;
			s.push(x);
		}
	}
	vector<int> v;
	while(!s.empty())
	{
		int x=s.top();s.pop();
		v.push_back(x);
	}
	for(int i=(int)v.size()-1;i>=0;i--)
	{
		now=(now+v[i])%n;
		if(now<0)now+=n;
	}
	printf("%d\n",now);
	return 0;
}
