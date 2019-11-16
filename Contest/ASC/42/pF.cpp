#include <stdio.h>
int max(int a,int b){return a>b?a:b;}
void solve(int n,int m){
	int l=0,r=0,x,tn=n,tm=m;
	x=max(n,m);
	for(long long int i=2;i*i<=x;i++){
		while(n%i==0){
			n/=i;
			l++;
		}
		while(m%i==0){
			m/=i;
			r++;
		}
		x=max(n,m);
	}
	if(n>1)l++;
	if(m>1)r++;
	if(l>r)printf("%d %d - Vera\n",tn,tm);
	else printf("%d %d - Harry\n",tn,tm);
}
int main(){
	freopen("funny.in","r",stdin);
	freopen("funny.out","w",stdout);
	int n,m;
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)return 0;
		solve(n,m);
	}
}
