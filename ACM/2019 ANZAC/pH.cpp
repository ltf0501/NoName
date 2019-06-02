#include <stdio.h>
int main(){
	int q,m,a,b,ans=0;
	scanf("%d%d%d%d",&q,&m,&a,&b);
	ans=(b/m)*q;
	b%=m;
	if(b==0){
		ans+=(a+m-1)/m;
	}
	else{
		ans+=q;
		if(a>q*(m-b)){
			a-=q*(m-b);
			ans+=((a+m-1)/m);
		}
	}
	printf("%d\n",ans);
}
