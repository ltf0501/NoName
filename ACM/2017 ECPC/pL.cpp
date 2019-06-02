#include <stdio.h>
int main(){
	freopen("lazy.in","r",stdin);
	int t,n;
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d",&n);
		printf("Case %d: %d\n",i,n-1);
	}
}
