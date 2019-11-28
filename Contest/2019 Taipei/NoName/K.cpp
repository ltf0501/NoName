#include <stdio.h>
#include <queue>
using namespace std;
const int N=1e3+10;
void solve(){
	int a[N],n,l,r,ans=0;
	priority_queue<int,vector<int>,greater<int>> pq;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)pq.push(a[i]);
	for(int i=2;i<=n;i++){
		l=pq.top();
		pq.pop();
		r=pq.top();
		pq.pop();
		ans+=l+r;
		pq.push(l+r);
	}
	printf("%d\n",ans);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)solve();
}
