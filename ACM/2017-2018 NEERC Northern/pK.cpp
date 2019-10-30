#include <stdio.h>

int main(){
#ifdef ONLINE_JUDGE
	freopen("kotlin.in", "r", stdin);
	freopen("kotlin.out", "w", stdout); 
#endif
	int h,w,n;
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(i*j==n&&(i*2-1<=h&&j*2-1<=w)){
				for(int x=1;x<i;x++){
					for(int y=1;y<j;y++)printf(".#");
					for(int y=j*2-1;y<=w;y++)printf(".");
					printf("\n");
					for(int y=1;y<=w;y++)printf("#");
					printf("\n");
				}
				for(int x=i*2-1;x<=h;x++){
					for(int y=1;y<j;y++)printf(".#");
					for(int y=j*2-1;y<=w;y++)printf(".");
					printf("\n");
				}
				return 0;
			}
		}
	}
	printf("Impossible\n");
}
