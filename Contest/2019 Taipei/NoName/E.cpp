#include <bits/stdc++.h>
int max(int a,int b){return a>b?a:b;}
void solve(){
	int k,l,x,y;
	scanf("%d%d",&k,&l);
	if(l>=2000){
		printf("-1\n");
		return ;
	}
	y=max(501,(k+3998+1997)/1998);
	x=(y-2)*1999-k;
	printf("1999\n");
	printf("%d %d",x,-x-1);
	for(int i=3;i<=1997;i++)printf(" 0");
	printf(" -1 %d\n",y);
	assert(abs(x) <= 1000000 && abs(-x - 1) <= 1000000);
	assert(abs(y) <= 1000000);
	int ans = max(1999 * (y - 2), 1995 * (y - 1));
	int greedy = x;
	assert(ans - greedy == k);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)solve();
}
// x, -x + 1, -1, -1, 0, ..., 0, -1, y
// 1999(y - 2) - x <= 1998y - 3998
// 1999(y - 2) - x = k;
// 1999(y - 2) >= 1995(y - 1)
// 4y >= 1999 * 2 - 1995 = 3998 - 1995 = 2003
// y >= 501
