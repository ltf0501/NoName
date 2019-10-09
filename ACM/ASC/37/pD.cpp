#include <stdio.h>
const int N=2e2+10;
void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
	return ;
}
int main(){
	
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	int n,a[N][N],pos,ans[N];
	scanf("%d",&n);
	for(int i=1;i<n;i++)for(int j=0;j<i;j++)scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)ans[i]=i;
	for(int i=1;i<n;i++){
		pos=n-i+1;
		for(int j=0;j<i;j++){
			if(a[pos-1][n-i-1]==1){
				if(ans[pos]>ans[pos-1])swap(ans[pos],ans[pos-1]);
				else{
					printf("NO\n");
					return 0;
				}
			}
			else {
				if(ans[pos]<ans[pos-1]){
					printf("NO\n");
					return 0;
				}
			}
			pos++;
		}
	}
	printf("YES\n%d",ans[1]);
	for(int i=2;i<=n;i++)printf(" %d",ans[i]);
	printf("\n");
}
