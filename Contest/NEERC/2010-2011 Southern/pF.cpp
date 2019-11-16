#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int N=1e2+10;
#define PB push_back
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,now,f,temp;
	bool went[N],ppl[N];
	queue<int> q;
	vector<int> v;
	scanf("%d%d",&n,&f);
	for(int i=0;i<N;i++)went[i]=ppl[i]=false;
	for(int i=0;i<n;i++){
		scanf("%d",&temp);
		q.push(temp);
		ppl[temp]=true;
	}
	while(!q.empty()){
		now=q.front();
		q.pop();
		if(went[now])continue;
		while(f<now){
			f++;
			if(!went[f]&&ppl[f]){
				went[f]=true;
				v.PB(f);
				ppl[f]=false;
			}
		}
		while(f>now){
			f--;
			if(!went[f]&&ppl[f]){
				went[f]=true;
				v.PB(f);
				ppl[f]=false;
			}
		}
	}
	printf("%d",v[0]);
	for(int i=1;i<v.size();i++)printf(" %d",v[i]);
	printf("\n");
}

