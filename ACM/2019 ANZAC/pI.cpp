#include <stdio.h>
int main(){
	long long int n,now=1,m,ans=0,cnt=1;
	scanf("%lld%lld",&n,&m);
	while(m>=now){
		//printf("now=%d cnt=%d ans=%d\n",now,cnt,ans);
		if(m-cnt-now+1<n-cnt-1){
			ans+=now;
			now++;
			for(int i=cnt+2;i<=n;i++,m--)ans+=m;
			printf("%lld\n",ans);
			return 0;
		}
		ans+=now;
		now+=cnt;
		cnt++;
	}
	//printf("here\n");
	printf("%lld\n",ans);
}
