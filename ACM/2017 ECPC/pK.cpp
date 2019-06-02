#include <stdio.h>
int min(int a,int b){return a>b?b:a;}
int main(){
	freopen("katryoshka.in","r",stdin);
	int t,n,m,k,temp,ans;
	scanf("%d",&t);
	for(int o=1;o<=t;o++){
		scanf("%d%d%d",&n,&m,&k);
		ans=0;
		temp=min(n,min(m,k));
		n-=temp;
		m-=temp;
		k-=temp;
		ans+=temp;
		temp=min(n/2,k);
		ans+=temp;
		printf("Case %d: %d\n",o,ans);
	}
}
