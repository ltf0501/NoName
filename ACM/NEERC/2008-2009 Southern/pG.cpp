#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define PB push_back
const int N=5e1+10;
int main(){
	int n,x,k,temp;
	set<int> s[N];
	vector<int> ans;
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&k);
		while(k--){
			scanf("%d",&temp);
			s[i].insert(temp);
		}
	}
	for(int i:s[x]){
		for(int j:s[i])if(j!=x&&s[x].find(j)==s[x].end())ans.PB(j);
	}
	sort(ans.begin(),ans.end());
	ans.resize(unique(ans.begin(),ans.end())-ans.begin());
	if(ans.empty())printf("0\n");
	else{
		printf("%d\n%d",(int)ans.size(),ans[0]);
		for(int i=1;i<ans.size();i++)printf(" %d",ans[i]);
		printf("\n");
	}
}
