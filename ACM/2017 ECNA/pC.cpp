#include<bits/stdc++.h>
using namespace std;
#define maxn 15010
char s[maxn];
int main()
{
	scanf("%s",s);
	int n=strlen(s);
	int tot=0;
	for(int i=0;i<n/2;i++)tot+=(s[i]-'A');
	tot%=26;
	for(int i=0;i<n/2;i++)
	{
		if(s[i]+tot<='Z')s[i]+=tot;
		else s[i]=(s[i]+tot-26);
	}
	tot=0;
	for(int i=0;i<n/2;i++)tot+=(s[i+n/2]-'A');
	tot%=26;
	for(int i=0;i<n/2;i++)
	{
		if(s[i+n/2]+tot<='Z')s[i+n/2]+=tot;
		else s[i+n/2]=(s[i+n/2]+tot-26);
	}
	for(int i=0;i<n/2;i++)
	{
		int num=s[i+n/2]-'A';
		if(s[i]+num<='Z')s[i]+=num;
		else s[i]=(s[i]+num-26);
	}
	for(int i=0;i<n/2;i++)putchar(s[i]);puts("");
	return 0;
}
