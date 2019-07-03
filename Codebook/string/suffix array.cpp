#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
char c[maxn];
int sa[maxn],rk[maxn],h[maxn];
int t1[maxn],t2[maxn],cnt[maxn];
int n,m;
void build_sa()
{
    m=26;
    int *x=t1,*y=t2;
    for(int i=0;i<n;i++)cnt[x[i]=(c[i]-'a')]++;
    for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
    for(int i=n-1;i>=0;i--)sa[--cnt[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-k;i<n;i++)y[p++]=i;
        for(int i=0;i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
        for(int i=0;i<m;i++)cnt[i]=0;
        for(int i=0;i<n;i++)cnt[x[y[i]]]++;
        for(int i=1;i<m;i++)cnt[i]+=cnt[i-1];
        for(int i=n-1;i>=0;i--)sa[--cnt[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(int i=1;i<n;i++)
            x[sa[i]]=(y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]) ? p-1 : p++;
        if(p>=n)break;
        m=p;
    }
    for(int i=0;i<n;i++)rk[sa[i]]=i;
}
void build_hei()
{
    int k=0;
    for(int i=0;i<n;i++)
    {
        if(k)k--;
        int j=sa[rk[i]-1];
        while(c[i+k]==c[j+k])k++;
        h[rk[i]]=k;
    }
}
main()
{
    scanf("%s",c);
    n=strlen(c);
    build_sa();
	build_hei();
	return 0;
}
