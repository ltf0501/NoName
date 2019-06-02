#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=1e5+10;
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}
int main(){
	int n,a[N],ans=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	sort(a,a+n);
	for(int i=0;i<n;i++){
		ans=max(ans,min(a[i],n-i));
	}
	printf("%d\n",ans);
}
