bool debug=false;
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <utility>
using namespace std;
#define PB push_back
#define F first
#define S second
const int INF=1e6+10;
int max(int a,int b){return a>b?a:b;}
int main(){
	int r,s,n,x,y,ans=0;
	vector<int> v;
	scanf("%d%d%d",&r,&s,&n);
	while(n--){
		scanf("%d%d",&x,&y);
		if(y>s)v.PB(r-x+y-s);
		else v.PB(r-x+s-y+1);
	}
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	for(int i=0;i<v.size();i++){
		ans=max(v[i]+i,ans);
	}
	printf("%d\n",ans+1);
}
