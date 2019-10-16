#include <stdio.h>
void solve(int n){
	if(n>6){
		printf("3\n");
		for(int i=1;i<n;i++)printf("%d ",i%2+1);
		printf("1\n");
		for(int i=1;i<n;i++)printf("3 ");
		printf("3\n");
	}
	else if(n==3){
		printf("1\n");
		for(int i=1;i<n;i++)printf("1 ");
		printf("1\n");
		for(int i=1;i<n;i++)printf("1 ");
		printf("1\n");
	}
	else {
		printf("2\n");
		for(int i=1;i<n;i++)printf("%d ",i%2+1);
		printf("1\n");
		for(int i=1;i<n;i++)printf("%d ",i%2+1);
		printf("1\n");
	}
	return ;
}
int main(){
	freopen("jubilee.in","r",stdin);
	freopen("jubilee.out","w",stdout);
	int n;
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		solve(n);
	}
}
