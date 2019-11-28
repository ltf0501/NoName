#include <stdio.h>
int main(){
	const int N=5e1+10;
	int a[N],n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)for(int k=1;k<=n;k++)if(i!=k&&j!=k){
		if((a[i]-a[j])%a[k]!=0){
			printf("no\n");
			return 0;
		}
	}
	printf("yes\n");
}
